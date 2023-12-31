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

std::mutex mutex1;
char* sharedMemory;

void *share(void *ptr);
void *share(void *ptr)
{
    std::lock_guard<std::mutex> lock(mutex1);

    sharedMemory = (char *)ptr;
    std::cout << sharedMemory << std::endl;

    return nullptr;
}

void *recvOdom();
void *recvOdom()
{   
    std::string recvMsg;
    char* recvOdom;
    Recv recv;
    recvMsg = recv.recvOdom();
    recvOdom = new char[recvMsg.length()+1]; //std array
    strcpy(recvOdom, recvMsg.c_str());
    share((void*)recvOdom);

    //delete[] recvOdom;
        std::cout << sharedMemory << std::endl;
    return nullptr;
}

void *scaleOdom();
void *scaleOdom()
{   
    std::string recvMsg = sharedMemory;
    std::string scaledMsg;
    char* scaledOdom;

    odomScaler Scaler;
    double dRecvMsg = Scaler.scale(recvMsg);
    scaledMsg = std::to_string(dRecvMsg);

    scaledOdom = new char[scaledMsg.length()+1];
    strcpy(scaledOdom, scaledMsg.c_str());
    share((void*)scaledOdom);

    //delete[] scaledOdom;
    std::cout << sharedMemory << std::endl;
    return nullptr;
}

int main(void)
{   
    std::thread thread1(*recvOdom);
    std::thread thread2(*scaleOdom);
    //std::thread thread3(*motorcontroller)

    thread1.join();
    thread2.join();

    return 0;
}
