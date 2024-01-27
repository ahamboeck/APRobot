#include "linearControl.h"

std::tuple<double, double> linearControl::calculateLinearControl(odomScaler::Odometry o){
    double v = 0;
    double omega = 0;
    linearControl controller;

    controller.odometry.odometry = o;
    controller.krho = 3;
    controller.kalpha = 8;
    controller.kbeta = -1.5;

    //calculate
    Eigen::Quaternion<double> q(controller.odometry.odometry.pose.orientation.w, 
                     controller.odometry.odometry.pose.orientation.x, 
                     controller.odometry.odometry.pose.orientation.y, 
                     controller.odometry.odometry.pose.orientation.z);

    Eigen::Vector3d euler = q.toRotationMatrix().eulerAngles(0, 1, 2);  // (roll, pitch, yaw)

    // // calculate
    controller.delta_x = controller.goalX - controller.odometry.odometry.pose.position.x;
    controller.delta_y = controller.goalY - controller.odometry.odometry.pose.position.y;
    controller.delta_th = controller.goalTheta - euler[2];
    controller.rho = sqrt(pow(controller.delta_x, 2) + pow(controller.delta_y, 2));
    controller.alpha = fmod((-euler[2] + atan2(controller.delta_y, controller.delta_x)), M_PI_2);
    controller.beta = fmod(-controller.delta_th - controller.alpha, M_PI);



    if(controller.rho < 0.2 &&  abs(controller.delta_th) < 0.2)
    {
        v = 0;
        omega = 0;
    }
    else
    {
        v = controller.krho * controller.rho;
        omega = controller.kalpha * controller.alpha + controller.kbeta * controller.beta;
    }

    return std::make_tuple(v, omega);
}