#include "odomScaler.h"

int main()
{
    std::string odom =  R"---({"header":{"seq":22567,"stamp":{"secs":1667561284,"nsecs":871624946},"frame_id":"odom"},"child_frame_id":"base_footprint",
                        "pose":{"pose":{"position":{"x":5.803671360015869,"y":-20.236299514770508,"z":0.0},"orientation":{"x":0.0,"y":0.0,"z":0.41925710439682007,
                        "w":0.9078675508499146}},"covariance":[0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0
                        ,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0]},"twist":{"twist":{"linear":{"x":0.2091853767633438,"y":0.0,"z":0.0},"angular":{"x": 0.0,"y":
                        0.0,"z": -0.009659458883106709}},"covariance":[0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,
                        0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0]}})---";

    odomScaler Scaler;
    Scaler.scale(odom);

    std::cout << Scaler.odometry.pose.position.x << std::endl;
    std::cout << Scaler.odometry.pose.position.y << std::endl;
    std::cout << Scaler.odometry.pose.position.z << std::endl;
    std::cout << Scaler.odometry.pose.orientation.x << std::endl;
    std::cout << Scaler.odometry.pose.orientation.y << std::endl;
    std::cout << Scaler.odometry.pose.orientation.z << std::endl;
    std::cout << Scaler.odometry.pose.orientation.w << std::endl;
    std::cout << Scaler.odometry.twist.linear.x << std::endl;
    std::cout << Scaler.odometry.twist.linear.y << std::endl;
    std::cout << Scaler.odometry.twist.linear.z << std::endl;
    std::cout << Scaler.odometry.twist.angular.x << std::endl;
    std::cout << Scaler.odometry.twist.angular.y << std::endl;
    std::cout << Scaler.odometry.twist.angular.z << std::endl;

    return 0;
}