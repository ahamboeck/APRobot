#include <iostream>
#include <map>
#include <string>
#include <vector>
#include <boost/algorithm/string.hpp>

int main()
{
    std::string odom =  R"---(---START---{"header":{"seq":22567,"stamp":{"secs":1667561284,"nsecs":871624946},"frame_id":"odom"},"child_frame_id":"base_footprint",
                        "pose":{"pose":{"position":{"x":5.803671360015869,"y":-20.236299514770508,"z":0.0},"orientation":{"x":0.0,"y":0.0,"z":0.41925710439682007,
                        "w":0.9078675508499146}},"covariance":[0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0
                        ,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0]},"twist":{"twist":{"linear":{"x":0.2091853767633438,"y":0.0,"z":0.0},"angular":{"x": 0.0,"y":
                        0.0,"z": -0.009659458883106709}},"covariance":[0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,
                        0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0]}}___END___)---";

    //nav_msgs::Odometry
    std::map<std::string, std::map<std::string, std::map<std::string, std::map<std::string, std::string>>>> Odometry;

    //significant odom pose data
    std::size_t startPose = odom.find("pose");
    std::size_t endPose   = odom.find("}}");
    std::string Pose      = odom.substr(startPose + 7, endPose - startPose -5);
    //pose.pose.position
    std::size_t startPos  = Pose.find("position");
    std::size_t endPos    = Pose.find("}");
    std::string position  = Pose.substr(startPos - 1, endPos + 2 - startPos);
    //position.x
    std::size_t startPx    = position.find(R"("x":)") + 4;
    std::size_t endPx      = position.find(",");
    std::string pX         = position.substr(startPx, endPx - startPx);
    //position.y
    std::size_t startPy    = position.find(R"("y":)");
    std::size_t endPy      = position.find(",");
    std::string pY         = position.substr(startPy + 4, endPy - 14);
    //position.z
    std::size_t startPz    = position.find(R"("z":)");
    std::size_t endPz      = position.find("}");
    std::string pZ         = position.substr(startPz + 4, endPz - 3);
    
    //pose.pose.orientation
    //std::size_t startOri    = Pose.find("orienation");
    //std::size_t endOri      = Pose.find("}");
    //std::string orientation = Pose.substr(startOri, (endOri + 1) - startOri);
    ////position.x
    //std::size_t startOx    = position.find("x");
    //std::size_t endOx      = position.find(",");
    //std::string oX         = position.substr(startOx, (endOx + 1) - startOx);
    ////position.y
    //std::size_t startOy    = position.find("y");
    //std::size_t endOy      = position.find(",");
    //std::string OY         = position.substr(startOy, (endOy + 1) - startOy);
    ////position.z
    //std::size_t startOz    = position.find("z");
    //std::size_t endOz      = position.find(",");
    //std::string oZ         = position.substr(startOz, (endOz + 1) - startOz);
    ////position.w
    //std::size_t startOw    = position.find("w");
    //std::size_t endOw      = position.find(",");
    //std::string oW         = position.substr(startOw, (endOw + 1) - startOw);

    //significant twist data
    //std::size_t startTwist = odom.find("twist");
    //std::size_t endTwist   = odom.find("}}", startTwist);
    //std::string Twist = odom.substr(startTwist, (endTwist + 2) - startTwist);

    //Odometry.pose
    //pose.pose.position
    std::string Odometry_pose_pose_position_x     = pX;
    std::string Odometry_pose_pose_position_y     = pX;
    std::string Odometry_pose_pose_position_z     = pZ;
    //pose.pose.orientation
    Odometry["pose"]["pose"]["orientation"]["x"]  = "0.0";//oX;
    Odometry["pose"]["pose"]["orientation"]["y"]  = "0.0";//OY;
    Odometry["pose"]["pose"]["orientation"]["z"]  = "0.0";//oZ;
    Odometry["pose"]["pose"]["orientation"]["w"]  = "0.0";//oW;

    //Odometry.twist
    //twist.twist.linear
    Odometry["twist"]["twist"]["linear"]["x"]     = "0.0";
    Odometry["twist"]["twist"]["linear"]["y"]     = "0.0";
    Odometry["twist"]["twist"]["linear"]["z"]     = "0.0";
    //twist.twist.angluar
    Odometry["twist"]["twist"]["angular"]["x"]    = "0.0";
    Odometry["twist"]["twist"]["angular"]["y"]    = "0.0";
    Odometry["twist"]["twist"]["angular"]["z"]    = "0.0";

    //std::cout << Odometry_pose_pose_positon_x << std::endl;
    std::cout << position << std::endl;

    return 0;
}

    //test
    //std::string Odometry_pose_pose_positon_x = Odometry["pose"]["pose"]["position"]["x"];
    //std::string Odometry_pose_pose_positon_y = Odometry["pose"]["pose"]["position"]["y"];

    //pose":{"pose":{"position":{"x":5.803671360015869,"y":-20.236299514770508,"z":0.0},"orientation":{"x":0.0,"y":0.0,"z":0.41925710439682007,"w":0.9078675508499146}}
    //position":{"x":5.803671360015869,"y":-20.236299514770508,"z":0.0}
    //"x":5.803671360015869