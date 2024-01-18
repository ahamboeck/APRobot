//odomScaler.cpp
#include "odomScaler.h"

double odomScaler::scale(std::string odom)
{
    std::string odometryData = odom;

    // pose.pose.position
    std::size_t startPos = odom.find("position");
    std::size_t endPos = odom.find("}");
    std::string position = odom.substr(startPos + 10, endPos - startPos -10);
    // position.x
    std::size_t startPx = position.find("\"x\":") + 4;
    std::size_t endPx = position.find(",", startPx);
    this->odometry.pose.position.x = std::stod(position.substr(startPx, endPx - startPx));
    // position.y
    std::size_t startPy = position.find("\"y\":") + 4;
    std::size_t endPy = position.find(",", startPy);
    this->odometry.pose.position.y = std::stod(position.substr(startPy, endPy - startPy));
    // position.z
    std::size_t startPz = position.find("\"z\":") + 4;
    std::size_t endPz = position.find("}", startPz);
    this->odometry.pose.position.z = std::stod(position.substr(startPz, endPz - startPz));

    // pose.pose.orientation
    std::size_t startOri = odom.find("orientation");
    std::size_t endOri = odom.find("}", endOri);
    std::string orientation = odom.substr(startOri + 13, endOri - startOri - 13);
    // orientation.y
    std::size_t startOy = orientation.find("\"y\":") + 4;
    std::size_t endOy = orientation.find(",", startOy);
    this->odometry.pose.orientation.y = std::stod(orientation.substr(startOy, endOy - startOy));
    // orientation.z
    std::size_t startOz = orientation.find("\"z\":") + 4;
    std::size_t endOz = orientation.find(",", startOz);
    this->odometry.pose.orientation.z = std::stod(orientation.substr(startOz, endOz - startOz));
    // orientation.w
    std::size_t startOw = orientation.find("\"w\":") + 4;
    std::size_t endOw = orientation.find("}", startOw);
    this->odometry.pose.orientation.w = std::stod(orientation.substr(startOw, endOw - startOw));

    // twist.twist.linear
    std::size_t startLinear = odom.find("linear");
    std::size_t endLinear = odom.find("}");
    std::string linear = odom.substr(startLinear + 7, endLinear - startLinear - 6);
    // linear.x
    std::size_t startLinearX = linear.find("\"x\":") + 4;
    std::size_t endLinearX = linear.find(",", startLinearX);
    this->odometry.twist.linear.x = std::stod(linear.substr(startLinearX, endLinearX - startLinearX));
    // linear.y
    std::size_t startLinearY = linear.find("\"y\":") + 4;
    std::size_t endLinearY = linear.find(",", startLinearY);
    this->odometry.twist.linear.y = std::stod(linear.substr(startLinearY, endLinearY - startLinearY));
    // linear.z
    std::size_t startLinearZ = linear.find("\"z\":") + 4;
    std::size_t endLinearZ = linear.find("}", startLinearZ);
    this->odometry.twist.linear.z = std::stod(linear.substr(startLinearZ, endLinearZ - startLinearZ));

    // twist.twist.angular
    std::size_t startAngular = odom.find("angular");
    std::size_t endAngular = odom.find("}");
    std::string angular = odom.substr(startAngular + 8, endAngular - startAngular - 7);
    // angular.x
    std::size_t startAngularX = angular.find("\"x\":") + 4;
    std::size_t endAngularX = angular.find(",", startAngularX);
    this->odometry.twist.angular.x = std::stod(angular.substr(startAngularX, endAngularX - startAngularX));
    // angular.y
    std::size_t startAngularY = angular.find("\"y\":") + 4;
    std::size_t endAngularY = angular.find(",", startAngularY);
    this->odometry.twist.angular.z = std::stod(angular.substr(startAngularY, endAngularY - startAngularY));
    // angular.z
    std::size_t startAngularZ = angular.find("\"z\":") + 4;
    std::size_t endAngularZ = angular.find("}", startAngularZ);
    this->odometry.twist.angular.z = std::stod(angular.substr(startAngularZ, endAngularZ - startAngularZ));

    //calculate

    double delta_x;
    double delta_y;
    double delta_th;

    double rho;
    double alpha;
    double beta; 
    double krho = 0.025;
    double kalpha = 0.03;
    double kbeta = -0.0125;
    double goalX = 1;
    double goalY = 1;
    double goalTheta = 0;

    // calculate
    delta_x = goalX - this->odometry.pose.position.x;
    delta_y = goalY - this->odometry.pose.position.y;
    delta_th = goalTheta - this->odometry.pose.orientation.z;
    rho = sqrt(pow(delta_x, 2) + pow(delta_y, 2));
    alpha = -this->odometry.pose.orientation.z + atan2(delta_y, delta_x);
    beta = -delta_th - alpha;

    if(rho < 0.3){
        this->vx = 0;
        this->omega = 0;
    }
    else{
        this->vx = krho * rho;
        this->omega = kalpha * alpha + kbeta * beta;
    }

    return 0;
}