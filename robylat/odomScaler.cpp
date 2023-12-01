#include <iostream>
#include <map>
#include <string>
#include <vector>
#include <boost/algorithm/string.hpp>

int main()
{
    std::string odom =  R"---("---START---{"header":{"seq":22567,"stamp":{"secs":1667561284,"nsecs":871624946},"frame_id":"odom"},"child_frame_id":"base_footprint",
                        "pose":{"pose":{"position":{"x":5.803671360015869,"y":-20.236299514770508,"z":0.0},"orientation":{"x":0.0,"y":0.0,"z":0.41925710439682007,
                        "w":0.9078675508499146}},"covariance":[0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0
                        ,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0]},"twist":{"twist":{"linear":{"x":0.2091853767633438,"y":0.0,"z":0.0},"angular":{"x": 0.0,"y":
                        0.0,"z": -0.009659458883106709}},"covariance":[0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,
                        0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0]}}___END___)---";

    std::string signiOdom;
    std::string pose;
    std::string orientation;
    std::map<std::string, std::map<std::string, std::map<std::string, double>>> Pose;

    //significant odom data
    std::size_t startOdom = odom.find("pose");
    std::size_t endOdom   = odom.find("}}", startOdom);
    signiOdom = odom.substr(startOdom, (endOdom + 2) -startOdom);

    //pose

    std::cout << signiOdom << std::endl;

    return 0;
}

    //Pose["pose"]["position"]["x"]       = 0.0;
    //Pose["pose"]["position"]["y"]       = 0.0;
    //Pose["pose"]["position"]["z"]       = 0.0;
    //Pose["pose"]["orientation"]["x"]    = 0.0;
    //Pose["pose"]["orientation"]["y"]    = 0.0;
    //Pose["pose"]["orientation"]["z"]    = 0.0;
    //Pose["pose"]["orientation"]["w"]    = 0.0;
    //odom.position
    //std::size_t startPos = odom.find("pose");
    //std::size_t endPos   = odom.find("}");
    //odom.orientation
    //std::size_t startOrien = odom.find("orientation");
    //std::size_t endOrien   = odom.find("},");


    //pose = odom.substr(startPos, endPos);
    //orientation = odom.substr(startOrien, endOrien);

