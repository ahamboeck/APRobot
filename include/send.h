#pragma once
#include "tcpHandler.h"
class Send : private TCPHandler
{
private:
public:
    Send(){};
    ~Send(){};
    void sendCmdVel(float linear, float angular)
    {
        //std::cout << "sendCmdVel is called!\n";
        echoServPort = 9999;
        std::stringstream ss;
        ss << "---START---{\"linear\":" << linear << ", \"angular\":" << angular << "}___END___";
        std::string echoString = ss.str();

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

        size_t echoStringLen = echoString.length();

        if (send(sock, echoString.c_str(), echoStringLen, 0) != static_cast<ssize_t>(echoStringLen))
            DieWithError("send() sent a different number of bytes than expected");
        //std::cout << std::endl;

        close(sock);
    }
};