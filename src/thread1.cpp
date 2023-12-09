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
int counter = 0;

void *print_message_value(void *ptr);
void *print_message_value(void *ptr)
{
    std::lock_guard<std::mutex> lock(mutex1);
    counter++;
    std::cout << "Counter Value: " << counter << std::endl;

    char *message = (char *)ptr;
    std::cout << message << std::endl;

    return nullptr;
}

int main(void)
{   
    const char *odom = "recieved-scaled-caluclated-toString";
    const char *recvOdom = "recvOdom";

    std::thread thread1(print_message_value, (void *)odom);
    std::thread thread2(print_message_value, (void *)recvOdom);

    thread1.join();
    thread2.join();

    return 0;
}