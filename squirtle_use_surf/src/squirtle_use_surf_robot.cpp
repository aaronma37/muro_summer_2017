#include <iostream>
#include "ros/ros.h"
#include "geometry_msgs/Pose.h"
#include "geometry_msgs/Twist.h"
using namespace std;

// function prototypes
void Velocity(geometry_msgs::Twist vel);
void CurrPose(geometry_msgs::Pose::ConstPtr& msg);

// global variables
ros::Subscriber Velocity_sub;
ros::Publisher Pose_pub;
geometry_msgs::Pose CURRENT;

int main(int argc, char **argv)
{ 
   
   // runs roscore
   ros::init(argc, argv, "squirtle_use_surf_robot");
   
   // node object declaration
   ros::NodeHandle n;
   
   // Subscriber to move the robot
   ros::Subscriber Velocity_sub = n.subscribe("Velocity", 100, Velocity);
   
   // Publishes the robot's position
   ros::Publisher Pose_pub = n.advertise<geometry_msgs::Pose>("Pose", 100);
   
   // Loop Frequency (Hz)
   ros::Rate rate(10);
   
   while (ros::ok())
      {
      ros::spinOnce();
      CurrPose();
      Velocity();
      rate.sleep();
      }
      
   return 0;      
}   
   
   
   
   // checks for incoming messages
 //  ros::spin();
  
void Velocity(geometry_msgs::Twist vel)
{
   
   vel.linear.x = speed;
   vel.linear.y = 0;
   vel.linear.z = 0;
   
   vel.angular.x = 0;
   vel.angular.y = 0;
   vel.angular.z = 0;
   
}
   
void CurrPose(const geometry_msgs::Pose::ConstPtr& msg)
{
  CURRENT.x = msg -> x;
  CURRENT.y = msg -> y;
  CURRENT.theta = msg -> theta;
  Pose_pub.publish(CURRENT);
  
  cout << CURRENT.x << endl;
}