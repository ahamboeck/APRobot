#include "tcpHandler.h"
#include "recieve.h"
#include "send.h"

int main()
{
    Send send;
    Recv recv;
    float l;
    float a;
    std::cout << "Set linear\n";
    std::cin >> l;
    std::cout << "Set angular\n";
    std::cin >> a;
    std::cout << "Linear: " << l << "  Angular: " << a << "\n";
    send.sendCmdVel(l, a);
    std::cout << "TEST4";
    recv.recvOdom();
    recv.recvScan();

    return 0;
}