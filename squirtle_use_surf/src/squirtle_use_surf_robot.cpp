#include <iostream>
#include "ros/ros.h"
#include "geometry_msgs/Pose2D.h"
#include "geometry_msgs/Twist.h"
ros::Publisher velocity_publisher;
using namespace std;

// function prototypes
void Velocity(

// global variables
geometry_msgs::Twist	VEL;
geometry_msgs::Pose2D	DESIRED, CURRENT;

int main(int argc, char **argv)
{ 
   double	cVal;
 
   // assigns the constant for the controller
   cout << "What constant value would you like? "; 
   cin >> cVal;
   cout << cVal << endl;
   
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
   
   double t0 = ros::Time::now().toSec();
   double current_distance;
   ros::Rate rate(10);
   
   velocity_publisher.publish(vel);
   double t1 = ros::Time::now().toSec();
   current_distance = speed * (t1 - t0);
   ros::spinOnce();
}
   
