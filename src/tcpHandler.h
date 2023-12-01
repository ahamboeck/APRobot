#include <iostream>
#include <cstdlib>     // For atoi() and exit()
#include <cstring>     // For memset()
#include <unistd.h>    // For close()
#include <sys/socket.h> // For socket(), connect(), send(), and recv()
#include <arpa/inet.h>  // For sockaddr_in and inet_addr()

#define RCVBUFSIZE 5000   // Size of receive buffer

void DieWithError(const std::string &errorMessage) { // Error handling function
    std::cerr << errorMessage << std::endl;
    exit(1);
}

int main(int argc, char *argv[])
{
    int sock;                        // Socket descriptor
    struct sockaddr_in echoServAddr; // Echo server address
    unsigned short echoServPort;     // Echo server port
    const std::string servIP;        // Server IP address (dotted quad)
    const std::string echoString;    // String to send to echo server
    char echoBuffer[RCVBUFSIZE];     // Buffer for echo string
    unsigned int echoStringLen;      // Length of string to echo
    int bytesRcvd, totalBytesRcvd;   // Bytes read in single recv() and total bytes read
    servIP = "192.168.100.52";       // First arg: server IP address (dotted quad)
    void sendCmdVel(float linear, float angular)
    {
        atoi("9999")
        int linearValue = linear;
        int angularValue = angular;
        std::stringstream ss;
        ss << "---START---{\"linear\":" << linearValue << ", \"angular\":" << angularValue << "}___END___";
        std::string echoString = ss.str();

            // Create a reliable, stream socket using TCP
    if ((sock = socket(PF_INET, SOCK_STREAM, IPPROTO_TCP)) < 0)
        DieWithError("socket() failed");

    // Construct the server address structure
    memset(&echoServAddr, 0, sizeof(echoServAddr));    // Zero out structure
    echoServAddr.sin_family      = AF_INET;            // Internet address family
    echoServAddr.sin_addr.s_addr = inet_addr(servIP);  // Server IP address
    echoServAddr.sin_port        = htons(echoServPort); // Server port

    // Establish the connection to the echo server
    if (connect(sock, (struct sockaddr *) &echoServAddr, sizeof(echoServAddr)) < 0)
        DieWithError("connect() failed");

    echoStringLen = strlen(echoString); // Determine input length

    // Send the string to the server
    if (send(sock, echoString, echoStringLen, 0) != static_cast<int>(echoStringLen))
        DieWithError("send() sent a different number of bytes than expected");

    // Receive the same string back from the server
    totalBytesRcvd = 0;
    std::cout << "Received: "; // Setup to print the echoed string
    while (totalBytesRcvd < echoStringLen)
    {
        // Receive up to the buffer size (minus 1 to leave space for a null terminator) bytes from the sender
        if ((bytesRcvd = recv(sock, echoBuffer, RCVBUFSIZE - 1, 0)) <= 0)
        {
            DieWithError("recv() failed or connection closed prematurely, closed sock");
            close(sock);
        }
        else
        {
            totalBytesRcvd += bytesRcvd;   // Keep tally of total bytes
            echoBuffer[bytesRcvd] = '\0';  // Terminate the string!
            std::cout << echoBuffer;       // Print the echo buffer
        }
    }

    std::cout << std::endl; // Print a final linefeed

    close(sock);
    }