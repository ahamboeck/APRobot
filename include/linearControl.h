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
    ~linearControl(

    ){        std::cout << "Linear Controler destructed" << std::endl;};

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
    double goalX = 1;
    double goalY;
    double goalTheta;

    bool goalReached;
    int  goalIndex;

    //double b = 2;
    //double c = 1;
    //double d;
    //double piRad =  M_1_PI/180;

    //std::array<std::tuple<double, double, double>, 3> goals = { 
    //    // std::make_tuple(b, 0.0, 0),
    //    // std::make_tuple(b+c/2, c/2, 30*piRad),
    //    // std::make_tuple(b+c, c, 0),
    //    // std::make_tuple(b+1.5*c, c/2, -30*piRad),
    //    // std::make_tuple(b+2*c, 0, -60*piRad),
    //    // std::make_tuple(b+1.5*c, -c/2, 180*piRad),
    //    // std::make_tuple(b+c, -c, 210*piRad),
    //    // std::make_tuple(b+c/2, -c/2, 180*piRad),
    //    std::make_tuple(0.5, 0, 0),
    //    std::make_tuple(1, 0.0, 0),
    //    std::make_tuple(1.5, 0, 0),
    //    //std::make_tuple(2, 0, 0),
    //    //std::make_tuple(1.5, -0.5,0),
    //    //std::make_tuple(1, 0, 0),
    //    //std::make_tuple(0, 0, 0),
    //};

    int getIndex();
    std::tuple<double, double, bool> calculateLinearControl(odomScaler::Odometry o, double goalX, double goalY, double goalTheta);
    double wrapAngle(double angle);
};