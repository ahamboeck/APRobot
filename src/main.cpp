#include <stdio.h>
#include <stdlib.h>
#include <thread>
#include <iostream>
#include <mutex>
#include <linearControl.h>
#include <string>
#include <send.h>
#include <recieve.h>
#include <mutex>
#include <condition_variable>
#include <atomic>
#include <localization.h>



std::mutex mutex1;
std::condition_variable cv;

std::shared_ptr<odomScaler::Odometry> sharedOdometry;
char *sharedMemory;
double *sharedVx;
double *sharedOmega;
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

            sharedMemory = nullptr;
            sharedVx = nullptr;
            sharedOmega = nullptr;
            sharedOdometry = nullptr;
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
    // std::cout << "Run scaleOdom thread \n";
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

    odomScaler::Odometry o = *sharedOdometry;

    linearControl controller;

    std::tuple<double, double> vxOmega = controller.calculateLinearControl(o);

    sharedVx = new double(std::get<0>(vxOmega));
    sharedOmega = new double(std::get<1>(vxOmega));

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

        dataReady = true;
        cv.notify_one();
    }
    return nullptr;
}

localization locator;

int main(void)
{
    std::thread exitThread(checkForExit);

    while (!stop.load())
    {
        locator.center();
        locator.pyPlot();
        
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