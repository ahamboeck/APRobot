//odomScaler.h
#include <iostream>
#include <map>
#include <string>
#include <vector>
#include "../lib/boost/algorithm/string.hpp"
#include <cmath>
#include "../lib/eigen3/Eigen/Core"
#include "../lib/eigen3/Eigen/Geometry"

class odomScaler
{ 
private:

public:
    struct Odometry
    {  
        struct Pose
        {
            struct Position
            {
                double x, y, z;
            }position;

            struct Orientation
            {
                double x, y, z, w;
            }orientation;
        }pose;

        struct Twist
        {
            struct Linear
            {
                double x, y, z;
            } linear;

            struct Angular
            {
                double x, y, z;
            } angular;
        }twist;
    };
    
    //default constructor
    odomScaler() {};
    //default destructor
    ~odomScaler() {};
    //msg
    Odometry odometry;
    //scaling
    double scale(std::string odom);
    double vx;
    double omega;
};