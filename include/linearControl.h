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
linearControl() : goalIndex(0), goalReached(false) {};
    ~linearControl(){
        goalIndex = 0;
        goalReached = false;
    };


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

    bool goalReached = false;
    int goalIndex = 0;

    std::array<std::tuple<double, double, double>, 5> goals = { 
        std::make_tuple(0.5, 0.0, 0),
        std::make_tuple(0.5, 0.5, 0),
        std::make_tuple(1.0, 1.0, 0),
        std::make_tuple(1.5, 1.0, 0),
        std::make_tuple(1.5, 1.5, M_1_PI/2)
    };


    std::tuple<double, double> calculateLinearControl(odomScaler::Odometry o);
    double wrapAngle(double angle);
};