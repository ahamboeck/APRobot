#pragma once
#include "tcpHandler.h"

class Recv : private TCPHandler
{
private:
    static const int RCVBUFSIZE = 99999999;
    std::string echoBuffer;
    int bytesRcvd, totalBytesRcvd;

public:
    Recv(){};
    ~Recv(){};
    std::string recvOdom()
    {
        std::cout << "recvOdom is called!\n";
        echoServPort = 9998;
        if ((sock = socket(PF_INET, SOCK_STREAM, IPPROTO_TCP)) < 0)
            DieWithError("socket() failed");
        memset(&echoServAddr, 0, sizeof(echoServAddr));
        echoServAddr.sin_family = AF_INET;
        echoServAddr.sin_addr.s_addr = inet_addr(servIP.c_str());
        echoServAddr.sin_port = htons(echoServPort);
        if (connect(sock, (struct sockaddr *)&echoServAddr, sizeof(echoServAddr)) < 0)
        {
            DieWithError("connect() failed");
        }

        // size_t echoStringLen = echoString.length();

        // if (send(sock, echoString.c_str(), echoStringLen, 0) != static_cast<ssize_t>(echoStringLen))
        //     DieWithError("send() sent a different number of bytes than expected");

        totalBytesRcvd = 0;
        echoBuffer.resize(RCVBUFSIZE);
        std::cout << "Received: ";
        if ((bytesRcvd = recv(sock, &echoBuffer[0], RCVBUFSIZE - 1, 0)) <= 0)
        {
            DieWithError("recv() failed or connection closed prematurely");
            close(sock);
            return "";
        }
        totalBytesRcvd += bytesRcvd;
        echoBuffer.resize(bytesRcvd); // Resize the string to the actual received size
        std::cout << echoBuffer << std::endl;

        close(sock);
        return echoBuffer;
    }
    
    std::string recvScan()
    {
        std::cout << "recvScan is called!\n";
        echoServPort = 9997;
        if ((sock = socket(PF_INET, SOCK_STREAM, IPPROTO_TCP)) < 0)
            DieWithError("socket() failed");
        memset(&echoServAddr, 0, sizeof(echoServAddr));
        echoServAddr.sin_family = AF_INET;
        echoServAddr.sin_addr.s_addr = inet_addr(servIP.c_str());
        echoServAddr.sin_port = htons(echoServPort);
        if (connect(sock, (struct sockaddr *)&echoServAddr, sizeof(echoServAddr)) < 0)
        {
            DieWithError("connect() failed");
        }

        // size_t echoStringLen = echoString.length();

        // if (send(sock, echoString.c_str(), echoStringLen, 0) != static_cast<ssize_t>(echoStringLen))
        //     DieWithError("send() sent a different number of bytes than expected");

        totalBytesRcvd = 0;
        echoBuffer.resize(RCVBUFSIZE);
        std::cout << "Received: ";
        if ((bytesRcvd = recv(sock, &echoBuffer[0], RCVBUFSIZE - 1, 0)) <= 0)
        {
            DieWithError("recv() failed or connection closed prematurely");
            close(sock);
            return "";
        }
        totalBytesRcvd += bytesRcvd;
        echoBuffer.resize(bytesRcvd); // Resize the string to the actual received size
        std::cout << echoBuffer << std::endl;

        close(sock);
        return echoBuffer;
    }
};