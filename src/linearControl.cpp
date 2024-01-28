#include "linearControl.h"

double linearControl::wrapAngle(double angle)
{
    while (angle > M_PI)
        angle -= 2 * M_PI;
    while (angle < -M_PI)
        angle += 2 * M_PI;
    return angle;
}

std::tuple<double, double, bool> linearControl::calculateLinearControl(odomScaler::Odometry o, double goalX, double goalY, double goalTheta)
{   
    this->goalX =     goalX;
    this->goalY =     goalY;
    this->goalTheta = goalTheta;

    double v = 0;
    double omega = 0;

    this->odometry.odometry = o;
    this->krho = 0.3*2.5; 
    this->kalpha = 0.8*2.5; 
    this->kbeta = -0.15*2.5;  

    // calculate
    Eigen::Quaternion<double> q(this->odometry.odometry.pose.orientation.w,
                                this->odometry.odometry.pose.orientation.x,
                                this->odometry.odometry.pose.orientation.y,
                                this->odometry.odometry.pose.orientation.z);

    euler = q.toRotationMatrix().eulerAngles(0, 1, 2); // (roll, pitch, yaw)

    // calculate
    this->delta_x = this->goalX - this->odometry.odometry.pose.position.x;
    this->delta_y = this->goalY - this->odometry.odometry.pose.position.y;
    this->delta_th = wrapAngle(this->goalTheta - euler[2]);

    this->rho = sqrt(pow(this->delta_x, 2) + pow(this->delta_y, 2));
    this->alpha = wrapAngle(atan2(this->delta_y, this->delta_x) - euler[2]);
    this->beta = wrapAngle(this->delta_th - alpha);

    if (this->rho < 0.3 && abs(this->delta_th) < 0.3)
    {
        this->goalReached = true;
        v = 0;
        omega = 0;
    }
    else
    {   
        this->goalReached = false;
        v = this->krho * this->rho;
        omega = this->kalpha * this->alpha + this->kbeta * this->beta;
    }

    return std::make_tuple(v, omega, goalReached);
}