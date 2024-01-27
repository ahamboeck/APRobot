#include <iostream>
#include <eigen3>

class linearControl
{
private:

    double delta_x;
    double delta_y;
    double delta_th;

    double rho;
    double alpha;
    double beta; 
    double krho = 0.2;
    double kalpha = 0.3;
    double kbeta = -0.05;
    double goalX = 2;
    double goalY = 0;
    double goalTheta = 1;
public:
    linearControl();
    ~linearControl();
};

linearControl::linearControl()
{
}

linearControl::~linearControl()
{
}
