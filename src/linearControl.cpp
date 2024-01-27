#include "linearControl.h"

double linearControl::wrapAngle(double angle)
{
    while (angle > M_PI)
        angle -= 2 * M_PI;
    while (angle < -M_PI)
        angle += 2 * M_PI;
    return angle;
}

std::tuple<double, double> linearControl::calculateLinearControl(odomScaler::Odometry o)
{
    double v = 0;
    double omega = 0;
    linearControl controller;

    controller.odometry.odometry = o;
    controller.krho = 0.3;
    controller.kalpha = 0.8;
    controller.kbeta = -0.15;
    controller.goalX = 1;
    controller.goalY = 1;
    controller.goalTheta = M_PI;

    // calculate
    Eigen::Quaternion<double> q(controller.odometry.odometry.pose.orientation.w,
                                controller.odometry.odometry.pose.orientation.x,
                                controller.odometry.odometry.pose.orientation.y,
                                controller.odometry.odometry.pose.orientation.z);

    Eigen::Vector3d euler = q.toRotationMatrix().eulerAngles(0, 1, 2); // (roll, pitch, yaw)

    // // calculate

    controller.delta_x = controller.goalX - controller.odometry.odometry.pose.position.x;
    controller.delta_y = controller.goalY - controller.odometry.odometry.pose.position.y;
    controller.delta_th = wrapAngle(controller.goalTheta - euler[2]);

    controller.rho = sqrt(pow(controller.delta_x, 2) + pow(controller.delta_y, 2));
    controller.alpha = wrapAngle(atan2(controller.delta_y, controller.delta_x) - euler[2]);
    controller.beta = wrapAngle(controller.delta_th - alpha);

    if (controller.rho < 0.2 && abs(controller.delta_th) < 0.2)
    {
        std::cout << "Goal Reached!!!\n";
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