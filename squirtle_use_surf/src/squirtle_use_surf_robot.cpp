#include <iostream>
#include "ros/ros.h"
#include "geometry_msgs/Pose2D.h"
#include "geometry_msgs/Twist.h"
ros::Publisher velocity_publisher;
using namespace std;

// function prototypes
void Velocity(speed);

// global variables
geometry_msgs::Twist	VEL;
geometry_msgs::Pose2D	CURRENT;

int main(int argc, char **argv)
{ 
   
   // runs roscore
   ros::init(argc, argv, "squirtle_use_surf_robot");
   
   // node object declaration
   ros::NodeHandle n;
   
   // Subscriber to move the robot
   ros::Subscriber Velocity_sub = n.subscribe("Velocity", 100, Velocity);
   
   // Publishes the robot's position
   ros::Publisher Pose_pub = n.advertise<geometry_msgs::Pose2D>("Pose", 100);
   
   // Loop Frequency (Hz)
   ros::Rate rate(10);
   
  
}   
   
   
   
   // checks for incoming messages
 //  ros::spin();
  
void Velocity(speed)
{
   geometry_msgs::Twist vel;   
   vel.linear.x = speed;
   vel.linear.y = 0;
   vel.linear.z = 0;
   
   vel.angular.x = 0;
   vel.angular.y = 0;
   vel.angular.z = 0;
   
}
   
