//thread1.cpp

#include <stdio.h>
#include <stdlib.h>
#include <thread>
#include <iostream>
#include <mutex>
#include <odomScaler.h>
#include <string>
#include <send.h>
#include <recieve.h>
#include <mutex>
#include <condition_variable>
#include <atomic>

std::mutex mutex1;
std::condition_variable cv;
char* sharedMemory;
char* sharedVx;
char* sharedOmega;
bool dataReady = false;

void *share(void *ptr);
void *share(void *ptr)
{
    std::lock_guard<std::mutex> lock(mutex1);

    sharedMemory = (char *)ptr;
    std::cout <<  "shared: " << sharedMemory << std::endl;

    dataReady = true;
    cv.notify_one();

    return nullptr;
}

void *recvOdom();
void *recvOdom()
{   
    std::string recvMsg;
    char* recvOdom;
    Recv recv;
    //test
    std::cout << "reached" << std::endl;
    //
    recvMsg = recv.recvOdom();
    //test
    std::cout << "reached1" << std::endl;
    //
    {
        std::lock_guard<std::mutex> lock(mutex1);
        recvOdom = new char[recvMsg.length()+1]; //std array
        strcpy(recvOdom, recvMsg.c_str());
        //share((void*)recvOdom);
        sharedMemory = recvOdom;
        dataReady = true;
    }
    //delete[] recvOdom;
    cv.notify_one();
    return nullptr;
}


void *scaleOdom();
void *scaleOdom()
{   
    std::unique_lock<std::mutex> lock(mutex1);
    cv.wait(lock, []{ return dataReady; });

    odomScaler Scaler;
    Scaler.scale(sharedMemory);

    std::string vxString = std::to_string(Scaler.vx);
    std::string omegaString = std::to_string(Scaler.omega);
    sharedVx = new char[vxString.length() + 1];
    sharedOmega = new char[omegaString.length() + 1];
    strcpy(sharedVx, vxString.c_str());
    strcpy(sharedOmega, omegaString.c_str());

    //delete[] scaledOdom;
    std::cout << sharedVx << std::endl;
    std::cout << sharedOmega << std::endl;

    dataReady = true;    
    cv.notify_one();
    return nullptr;
}

void *sendRobot();
void *sendRobot()
{   
    std::cout << "OUT" << std::endl;
    std::unique_lock<std::mutex> lock(mutex1);
    
    std::cout << "OUT 2" << std::endl;
    
    cv.wait(lock, []{ return dataReady; });
    

    float linear = std::stof(sharedVx);
    float angular = std::stof(sharedOmega);

    std::cout << "linear: " << linear << "angular:" << angular << std::endl;

    Send sender;
    sender.sendCmdVel(linear, angular);

    dataReady = true;    
    cv.notify_one();

    return nullptr;
}

int main(void)
{    

    while(true){
    std::thread thread1(*recvOdom);
    std::thread thread2(*scaleOdom);
    std::thread thread3(*sendRobot);
    
    thread1.join();
    thread2.join();
    thread3.join();

    //delete[] sharedMemory; // Cleanup
    //delete[] sharedVx;
    //delete[] sharedOmega;
    }

    return 0;
}
