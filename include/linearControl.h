#pragma once

#include <iostream>
#include <odomScaler.h>
#include <cmath>
#include "../lib/eigen3/Eigen/Core"
#include "../lib/eigen3/Eigen/Geometry"

class linearControl
{
public:
    linearControl(){};
    ~linearControl(){};

    odomScaler odometry;

    double delta_x;
    double delta_y;
    double delta_th;

    double rho;
    double alpha;
    double beta; 
    double krho;
    double kalpha;
    double kbeta;
    double goalX;
    double goalY;
    double goalTheta;
};