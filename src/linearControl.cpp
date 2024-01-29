#include "linearControl.h"

double linearControl::wrapAngle(double angle)
{
    while (angle > M_PI)
        angle -= 2 * M_PI;
    while (angle < -M_PI)
        angle += 2 * M_PI;
    return angle;
}

int linearControl::getIndex()
{
    return goalIndex;
}

std::tuple<double, double, bool> linearControl::calculateLinearControl(odomScaler::Odometry o, double goalX, double goalY, double goalTheta)
{
    double v = 0;
    double omega = 0;

    this->odometry.odometry = o;
    this->krho = 0.3;
    this->kalpha = 0.8;
    this->kbeta = -0.15;

    //set goal
    // this->goalX =      std::get<0>(this->goals[this->goalIndex]);
    // this->goalY =      std::get<1>(this->goals[this->goalIndex]);
    // this->goalTheta =  std::get<2>(this->goals[this->goalIndex]);
    //std::cout << "TopIndex: " << this->goalIndex << std::endl;

    // calculate
    Eigen::Quaternion<double> q(this->odometry.odometry.pose.orientation.w,
                                this->odometry.odometry.pose.orientation.x,
                                this->odometry.odometry.pose.orientation.y,
                                this->odometry.odometry.pose.orientation.z);

    Eigen::Vector3d euler = q.toRotationMatrix().eulerAngles(0, 1, 2); // (roll, pitch, yaw)

    // calculate
    this->delta_x = goalX - this->odometry.odometry.pose.position.x;
    this->delta_y = goalY - this->odometry.odometry.pose.position.y;
    this->delta_th = wrapAngle(goalTheta - euler[2]);

    this->rho = sqrt(pow(this->delta_x, 2) + pow(this->delta_y, 2));
    this->alpha = wrapAngle(atan2(this->delta_y, this->delta_x) - euler[2]);
    this->beta = wrapAngle(this->delta_th - alpha);

    if (this->rho < 0.2 && abs(this->delta_th) < 0.2)
    {
        //if (!this->goalReached) {
        //    //this->goalIndex++;
            this->goalReached = true;
        //}

        std::cout << "rho: " << this-> rho << " delta_th: " << this-> delta_th <<std::endl;

        std::cout << "goalX: " << this->goalX << " goalY: " << this->goalY << "   goalTheta: " << this->goalTheta << std::endl;

        std::cout << "deltaX: " << this->delta_x << "  deltaY: " << this->delta_y << "    deltaTh: " << this->delta_th << std::endl;

        std::cout << "posX: " << this->odometry.odometry.pose.position.x << "  posY: " << this->odometry.odometry.pose.position.y << 
        "   posYaw: " << euler[2] << std::endl;   

        std::cout << "ReachIndex: " << this->goalIndex << std::endl;    


        v = 0;
        omega = 0;

//        this->goalX =      std::get<0>(this->goals[this->goalIndex]);
//        this->goalY =      std::get<1>(this->goals[this->goalIndex]);
//        this->goalTheta =  std::get<2>(this->goals[this->goalIndex]);
    }
    else
    {   
        this->goalReached = false;
        v = this->krho * this->rho;
        omega = this->kalpha * this->alpha + this->kbeta * this->beta;
    }

    return std::make_tuple(v, omega, goalReached);
}