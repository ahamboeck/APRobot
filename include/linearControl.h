#pragma once

#include <iostream>
#include <odomScaler.h>
#include <cmath>
#include <tuple>
#include "../lib/eigen3/Eigen/Core"
#include "../lib/eigen3/Eigen/Geometry"

class linearControl
{
public:
linearControl(){};
    ~linearControl(){
        
        //std::cout << "rho: " << this-> rho << " delta_th: " << this-> delta_th <<std::endl;
        std::cout << "goalX: " << this->goalX << " goalY: " << this->goalY << "   goalTheta: " << this->goalTheta << std::endl;
        //std::cout << "deltaX: " << this->delta_x << "  deltaY: " << this->delta_y << "    deltaTh: " << this->delta_th << std::endl;
        //std::cout << "posX: " << this->odometry.odometry.pose.position.x << "  posY: " << this->odometry.odometry.pose.position.y 
        std::cout          << "   posYaw: " << euler[2] << std::endl;     
        //std::cout << "Linear Controler destructed" << std::endl;
    };

    odomScaler odometry;
    Eigen::Vector3d euler;

    double delta_x;
    double delta_y;
    double delta_th;
    double goalX;
    double goalY;
    double goalTheta;
    
    double rho;
    double alpha;
    double beta; 
    double krho;
    double kalpha;
    double kbeta;

    bool goalReached;

    std::tuple<double, double, bool> calculateLinearControl(odomScaler::Odometry o, double goalX, double goalY, double goalTheta);
    double wrapAngle(double angle);
};