#include <iostream>
#include <cstdlib>
#include <cstring>
#include <unistd.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <sstream>

#pragma once

class TCPHandler
{
protected:
    int sock;
    struct sockaddr_in echoServAddr;
    unsigned short echoServPort;
    const std::string servIP = "192.168.100.51";

public:
    TCPHandler()
    {
        std::cout << "Handler constructed\n";
    }
    ~TCPHandler()
    {
        std::cout << "Handler destructed\n";
    }
    void DieWithError(const std::string &errorMessage)
    {
        std::cerr << errorMessage << std::endl;
        std::cerr.flush(); // Ensure the buffer is flushed before exit
        exit(1);
    }

    // void sendCmdVel(float linear, float angular)
    // {
    //     std::cout << "sendCmdVel is called!\n";
    //     echoServPort = 9999;
    //     std::stringstream ss;
    //     ss << "---START---{\"linear\":" << linear << ", \"angular\":" << angular << "}___END___";
    //     std::string echoString = ss.str();

    //     if ((sock = socket(PF_INET, SOCK_STREAM, IPPROTO_TCP)) < 0)
    //         DieWithError("socket() failed");
    //     memset(&echoServAddr, 0, sizeof(echoServAddr));
    //     echoServAddr.sin_family = AF_INET;
    //     echoServAddr.sin_addr.s_addr = inet_addr(servIP.c_str());
    //     echoServAddr.sin_port = htons(echoServPort);
    //     if (connect(sock, (struct sockaddr *)&echoServAddr, sizeof(echoServAddr)) < 0)
    //     {
    //         DieWithError("connect() failed");
    //     }

    //     size_t echoStringLen = echoString.length();

    //     if (send(sock, echoString.c_str(), echoStringLen, 0) != static_cast<ssize_t>(echoStringLen))
    //         DieWithError("send() sent a different number of bytes than expected");
    //     // totalBytesRcvd = 0;
    //     // std::cout << "Received: ";
    //     // while (totalBytesRcvd < echoStringLen)
    //     // {
    //     //     std::cout << "Test 5\n";
    //     //     if ((bytesRcvd = recv(sock, echoBuffer, RCVBUFSIZE - 1, 0)) <= 0)
    //     //     {
    //     //         std::cout << "Test 8\n";
    //     //         DieWithError("recv() failed or connection closed prematurely");
    //     //         close(sock);
    //     //         return;
    //     //     }
    //     //     std::cout << "Test 7\n";
    //     //     totalBytesRcvd += bytesRcvd;
    //     //     echoBuffer[bytesRcvd] = '\0';
    //     //     std::cout << echoBuffer;
    //     // }
    //     std::cout << std::endl;

    //     close(sock);
    // }
};