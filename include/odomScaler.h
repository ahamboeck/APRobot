//odomScaler.h
#include <iostream>
#include <map>
#include <string>
#include <vector>
#include <boost/algorithm/string.hpp>

class odomScaler
{ 
private:
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

public:
    //default constructor
    odomScaler() {};
    //default destructor
    ~odomScaler() {};
    //msg
    Odometry odometry;
    //scaling
    void scale(std::string odom);
};