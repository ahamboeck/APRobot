#include "ros/ros.h"
#include "std_msgs/String.h"
#include "geometry_msgs/Twist.h"
#include "nav_msgs/Odometry.h"
#include "geometry_msgs/Pose.h"
#include <sstream>
#include <dynamic_reconfigure/server.h>
#include <turtle/reconfigureConfig.h>
#include "tf/transform_broadcaster.h"
#include "tf/LinearMath/Matrix3x3.h"
#include <tf/transform_datatypes.h>
#include <eigen3/Eigen/Core>
#include <cmath>

    // initialize
    // get_current_position
    nav_msgs::Odometry currentPose;
    geometry_msgs::Twist robotCmd;

    // calculate_velocity//publish
    bool   start;
    double rho;
    double alpha;
    double beta;
    double krho;
    double kalpha;
    double kbeta;
    double vx;
    double omega;
    double goalX;
    double goalY;
    double goalTheta;
    // calculate_euler
    double roll, pitch, yaw;

//Server reconfigure 
void callback(turtle::reconfigureConfig &config, uint32_t level)
{
  // Update the robot's movement status based on the start parameter
  start     = config.start;
  krho      = config.k_rho;
  kalpha    = config.k_alpha;
  kbeta     = config.k_beta;
  goalX     = config.goal_x;
  goalY     = config.goal_y;
  goalTheta = config.goal_theta;
}


void odomCallback(const nav_msgs::Odometry::ConstPtr& pose_msg)
{
  currentPose.pose.pose.position.x    =    pose_msg->pose.pose.position.x;
  currentPose.pose.pose.position.y    =    pose_msg->pose.pose.position.y;
  currentPose.pose.pose.position.z    =    pose_msg->pose.pose.position.z;
  currentPose.pose.pose.orientation.x =    pose_msg->pose.pose.orientation.x;
  currentPose.pose.pose.orientation.y =    pose_msg->pose.pose.orientation.y;
  currentPose.pose.pose.orientation.z =    pose_msg->pose.pose.orientation.z;
  currentPose.pose.pose.orientation.w =    pose_msg->pose.pose.orientation.w;
}

// calculate_euler
void calculateEuler()
{
    tf::Quaternion qua(currentPose.pose.pose.orientation.x, currentPose.pose.pose.orientation.y, currentPose.pose.pose.orientation.z, currentPose.pose.pose.orientation.w);
    tf::Matrix3x3 m(qua);
    tf::Matrix3x3 mat(qua);
    mat.getRPY(roll, pitch, yaw);
}

// calculate_velocity
void calculateVelocity()
{
    calculateEuler();

    double delta_x;
    double delta_y;
    double delta_th;

    // calculate
    delta_x = goalX - currentPose.pose.pose.position.x;
    delta_y = goalY - currentPose.pose.pose.position.y;
    delta_th = goalTheta - yaw;
    rho = sqrt(pow(delta_x, 2) + pow(delta_y, 2));
    alpha = -currentPose.pose.pose.orientation.z + atan2(delta_y, delta_x);
    beta = -delta_th - alpha;

    vx = krho * rho;
    omega = kalpha * alpha + kbeta * beta;

  if(rho < 0.3 || start != true) 
  {
    vx = 0.0;
    omega = 0.0;
  }
  else
  {
    robotCmd.linear.x = vx;   
    robotCmd.angular.z = omega;   
  }
}

int main(int argc, char **argv)
{
  ros::init(argc, argv, "turtle");
  ros::NodeHandle n;

  ros::Publisher chatter_pub = n.advertise<geometry_msgs::Twist>("/cmd_vel", 10);
  ros::Subscriber sub = n.subscribe("odom", 1000, odomCallback);
  
  dynamic_reconfigure::Server<turtle::reconfigureConfig> server;  
  dynamic_reconfigure::Server<turtle::reconfigureConfig>::CallbackType f;
  f = boost::bind(&callback, _1, _2);
  server.setCallback(f);


  ros::Rate loop_rate(10);

  int count = 0;
  while (ros::ok())
  {
    calculateVelocity();
    chatter_pub.publish(robotCmd);
    ros::spinOnce();
    loop_rate.sleep();
    ++count;
  }

  return 0;
}