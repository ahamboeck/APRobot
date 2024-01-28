#include <stdio.h>
#include <stdlib.h>
#include <thread>
#include <iostream>
#include <mutex>
#include "linearControl.h"
#include <string>
#include <send.h>
#include <recieve.h>
#include <mutex>
#include <condition_variable>
#include <atomic>
#include "localization.h"

double b = 1;
double c = 0.5;
double d;
double piRad = M_PI/180;

std::array<std::tuple<double, double, double>, 11> goals = {
std::make_tuple(0.3, 0.0, 0.0 * piRad),
std::make_tuple(0.6, 0.0, 90.0 * piRad),
std::make_tuple(0.72, 0.28, 45.0 * piRad),
std::make_tuple(1.0, 0.4, 0.0 * piRad),
std::make_tuple(1.28, 0.28, -45.0 * piRad),
std::make_tuple(1.4, 0.0, -90.0 * piRad),
std::make_tuple(1.28, -0.28, -135.0 * piRad),
std::make_tuple(1.0, -0.4, -180.0 * piRad),
std::make_tuple(0.72, -0.28, 135.0 * piRad),
std::make_tuple(0.6, 0, 180 * piRad),
std::make_tuple(0, 0, 0 * piRad),
};
 
std::mutex mutex1;
std::condition_variable cv;

std::shared_ptr<odomScaler::Odometry> sharedOdometry;
char *sharedMemory;
double *sharedVx;
double *sharedOmega;
bool *sharedReached;
int  goalIndex = 0;
bool dataReady = false;
std::atomic<bool> stop(false);

void checkForExit()
{
    int input;
    while (true) 
    {
        std::cin >> input;
        if (input == 0)
        {
            Send sender;
            sender.sendCmdVel(0, 0);
            delete[] sharedMemory;
            delete[] sharedVx;
            delete[] sharedOmega;
            delete[] sharedReached;


            sharedMemory = nullptr;
            sharedVx = nullptr;
            sharedOmega = nullptr;
            sharedOdometry = nullptr;
            sharedReached = nullptr;
            stop.store(true);
            break;
        }
    }
}

void *recvOdom();
void *recvOdom()
{
    std::string recvMsg;
    char *recvOdom;
    Recv recv;

    recvMsg = recv.recvOdom();
    {
        std::lock_guard<std::mutex> lock(mutex1);
        recvOdom = new char[recvMsg.length() + 1];
        strcpy(recvOdom, recvMsg.c_str());
        sharedMemory = recvOdom;
        dataReady = true;
    }
    cv.notify_one();
    return nullptr;
}

void *scaleOdom();
void *scaleOdom()
{
    std::unique_lock<std::mutex> lock(mutex1);
    cv.wait(lock, []
            { return dataReady; });

    odomScaler Scaler;
    Scaler.scale(sharedMemory);

    sharedOdometry = std::make_shared<odomScaler::Odometry>(Scaler.odometry);

    dataReady = true;
    cv.notify_one();
    return nullptr;
}

void *calculateVel();
void *calculateVel()
{
    std::unique_lock<std::mutex> lock(mutex1);
    cv.wait(lock, []
            { return dataReady; });

        if(goalIndex < goals.size()){
            
            if(sharedOdometry != nullptr){

                odomScaler::Odometry o = *sharedOdometry;

                linearControl controller;

                double goalX =      std::get<0>(goals[goalIndex]);
                double goalY =      std::get<1>(goals[goalIndex]);
                double goalTheta =  std::get<2>(goals[goalIndex]);

                std::tuple<double, double, bool> vxOmegaReached = controller.calculateLinearControl(o, goalX, goalY, goalTheta);
                
                sharedVx =      new double(std::get<0>(vxOmegaReached));
                sharedOmega =   new double(std::get<1>(vxOmegaReached));
                sharedReached = new bool(std::get<2>(vxOmegaReached));

                bool goalReached = *sharedReached;

                if(goalReached){
                    goalIndex ++;
                    goalReached = false;
                };
            };
        };
        
        dataReady = true;
        cv.notify_one();

    return nullptr;
}

void *sendRobot();
void *sendRobot()
{
    std::unique_lock<std::mutex> lock(mutex1);

    cv.wait(lock, []
            { return dataReady; });

    if (sharedVx != nullptr && sharedOdometry != nullptr)
    {
        double linear = *sharedVx;
        double angular = *sharedOmega;

        Send sender;
        sender.sendCmdVel(linear, angular);
    };

    dataReady = true;
    cv.notify_one();

    return nullptr;
}

int main(void)
{
    std::thread exitThread(checkForExit);

    while (!stop.load())
    {       
            std::thread thread1(*recvOdom);
            std::thread thread2(*scaleOdom);
            std::thread thread3(*calculateVel);
            std::thread thread4(*sendRobot);

            thread1.join();
            thread2.join();
            thread3.join();
            thread4.join();
    }

    if (exitThread.joinable())
    {
        exitThread.join();
    }

    return 0;
}