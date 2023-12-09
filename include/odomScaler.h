#include <iostream>
#include <map>
#include <string>
#include <vector>
#include <boost/algorithm/string.hpp>

class odomScaler
{ 
private:
    struct Position
    {
        double x, y, z;
    };

    struct Orientation
    {
        double x, y, z, w;
    };

    struct Pose
    {
        Position position;
        Orientation orientation;
    };

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
    };

public:
    //default constructor
    odomScaler() {};
    //default destructor
    ~odomScaler() {};
    
    struct Odometry
    {
        Pose pose;
        Twist twist;
    };

    Odometry scale(std::string odom);
};