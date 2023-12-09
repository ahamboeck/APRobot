#include <odomScaler.h>

//int main()
//{
//    std::string odom =  R"---({"header":{"seq":22567,"stamp":{"secs":1667561284,"nsecs":871624946},"frame_id":"odom"},"child_frame_id":"base_footprint",
//                        "pose":{"pose":{"position":{"x":5.803671360015869,"y":-20.236299514770508,"z":0.0},"orientation":{"x":0.0,"y":0.0,"z":0.41925710439682007,
//                        "w":0.9078675508499146}},"covariance":[0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0
//                        ,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0]},"twist":{"twist":{"linear":{"x":0.2091853767633438,"y":0.0,"z":0.0},"angular":{"x": 0.0,"y":
//                        0.0,"z": -0.009659458883106709}},"covariance":[0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,
//                        0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0]}})---";
//
//    odomScaler scaler;
//    scaler.scale(odom);
//    odomScaler::Odometry odometry = scaler.scale(odom);
//    
//    std::cout << odometry.pose.position.x << std::endl;
//    std::cout << odometry.pose.position.y << std::endl;
//    std::cout << odometry.pose.position.z << std::endl;
//    std::cout << odometry.pose.orientation.x << std::endl;
//    std::cout << odometry.pose.orientation.y << std::endl;
//    std::cout << odometry.pose.orientation.z << std::endl;
//    std::cout << odometry.pose.orientation.w << std::endl;
//    std::cout << odometry.twist.linear.x   << std::endl;
//    std::cout << odometry.twist.linear.y   << std::endl;
//    std::cout << odometry.twist.linear.z   << std::endl;
//    std::cout << odometry.twist.angular.x  << std::endl;
//    std::cout << odometry.twist.angular.y  << std::endl;
//    std::cout << odometry.twist.angular.z  << std::endl;
//
//    return 0;
//}

odomScaler::Odometry odomScaler::scale(std::string odom)
{
    Odometry odometry;
    odometry.pose.position.x;
    std::string odometryData = odom;

    //pose.pose.position
    std::size_t startPos = odom.find("position");
    std::size_t endPos = odom.find("}");
    std::string position = odom.substr(startPos + 10, endPos - startPos - 10);
    //position.x
    std::size_t startPx = position.find("\"x\":") + 4;
    std::size_t endPx = position.find(",", startPx);
    std::string pX = position.substr(startPx, endPx - startPx);
    //position.y
    std::size_t startPy = position.find("\"y\":") + 4;
    std::size_t endPy = position.find(",", startPy);
    std::string pY = position.substr(startPy, endPy - startPy);
    //position.z
    std::size_t startPz = position.find("\"z\":") + 4;
    std::size_t endPz = position.find("}", startPz);
    std::string pZ = position.substr(startPz, endPz - startPz);

    //pose.pose.orientation
    std::size_t startOri = odom.find("orientation");
    std::size_t endOri = odom.find("}");
    std::string orientation = odom.substr(startOri + 13, endOri - startOri - 13);
    //orientation.x
    std::size_t startOx = orientation.find("\"x\":") + 4;
    std::size_t endOx = orientation.find(",", startOx);
    std::string oX = orientation.substr(startOx, endOx - startOx);
    //orientation.y
    std::size_t startOy = orientation.find("\"y\":") + 4;
    std::size_t endOy = orientation.find(",", startOy);
    std::string oY = orientation.substr(startOy, endOy - startOy);
    //orientation.z
    std::size_t startOz = orientation.find("\"z\":") + 4;
    std::size_t endOz = orientation.find(",", startOz);
    std::string oZ = orientation.substr(startOz, endOz - startOz);
    //orientation.w
    std::size_t startOw = orientation.find("\"w\":") + 4;
    std::size_t endOw = orientation.find("}", startOw);
    std::string oW = orientation.substr(startOw, endOw - startOw);

    //twist.twist.linear
    std::size_t startLinear = odom.find("linear");
    std::size_t endLinear = odom.find("}");
    std::string linear = odom.substr(startLinear + 7, endLinear - startLinear - 6);
    //linear.x
    std::size_t startLinearX = linear.find("\"x\":") + 4;
    std::size_t endLinearX = linear.find(",", startLinearX);
    std::string lX = linear.substr(startLinearX, endLinearX - startLinearX);
    //linear.y
    std::size_t startLinearY = linear.find("\"y\":") + 4;
    std::size_t endLinearY = linear.find(",", startLinearY);
    std::string lY = linear.substr(startLinearY, endLinearY - startLinearY);
    //linear.z
    std::size_t startLinearZ = linear.find("\"z\":") + 4;
    std::size_t endLinearZ = linear.find("}", startLinearZ);
    std::string lZ = linear.substr(startLinearZ, endLinearZ - startLinearZ);

    //twist.twist.angular
    std::size_t startAngular = odom.find("angular");
    std::size_t endAngular = odom.find("}");
    std::string angular = odom.substr(startAngular + 8, endAngular - startAngular - 7);
    //angular.x
    std::size_t startAngularX = angular.find("\"x\":") + 4;
    std::size_t endAngularX = angular.find(",", startAngularX);
    std::string aX = angular.substr(startAngularX, endAngularX - startAngularX);
    //angular.y
    std::size_t startAngularY = angular.find("\"y\":") + 4;
    std::size_t endAngularY = angular.find(",", startAngularY);
    std::string aY = angular.substr(startAngularY, endAngularY - startAngularY);
    //angular.z
    std::size_t startAngularZ = angular.find("\"z\":") + 4;
    std::size_t endAngularZ = angular.find("}", startAngularZ);
    std::string aZ = angular.substr(startAngularZ, endAngularZ - startAngularZ);

    odometry.pose.position.x = std::stod(pX);
    odometry.pose.position.y = std::stod(pY);
    odometry.pose.position.z = std::stod(pZ);
    odometry.pose.orientation.x = std::stod(oX);
    odometry.pose.orientation.y = std::stod(oX);
    odometry.pose.orientation.z = std::stod(oY);
    odometry.pose.orientation.y = std::stod(oW);
    odometry.twist.linear.x = std::stod(lX);
    odometry.twist.linear.y = std::stod(lY);
    odometry.twist.linear.z = std::stod(lZ);
    odometry.twist.angular.x = std::stod(aX);
    odometry.twist.angular.y = std::stod(aY);
    odometry.twist.angular.z = std::stod(aZ);
    
    return Odometry();
}
