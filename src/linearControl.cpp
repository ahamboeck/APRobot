#include "linearControl.h"

    //calculate
    Eigen::Quaternion<double> q(this->odometry.pose.orientation.w, 
                     this->odometry.pose.orientation.x, 
                     this->odometry.pose.orientation.y, 
                     this->odometry.pose.orientation.z);

    Eigen::Vector3d euler = q.toRotationMatrix().eulerAngles(0, 1, 2);  // (roll, pitch, yaw)
    std::cout << "Euler: " << euler[2] << std::endl;



    // calculate
    delta_x = goalX - this->odometry.pose.position.x;
    delta_y = goalY - this->odometry.pose.position.y;
    delta_th = goalTheta - euler[2];
    rho = sqrt(pow(delta_x, 2) + pow(delta_y, 2));
    alpha = (-euler[2] + atan2(delta_y, delta_x)) ;
    beta = -delta_th - alpha;



    if(rho < 0.2 &&  abs(delta_th) < 0.2){
        this->vx = 0;
        this->omega = 0;
    }
    else{
        this->vx = krho * rho;
        this->omega = kalpha * alpha + kbeta * beta;
    }