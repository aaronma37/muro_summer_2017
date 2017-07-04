#include <iostream>
#include "ros/ros.h"
#include "geometry_msgs/Pose2D.h"
#include "turtlesim/Pose.h"
#include "geometry_msgs/Twist.h"
ros::Publisher velocity_publisher;
using namespace std;

// function prototypes
void DesiredPose(const geometry_msgs::Pose2D::ConstPtr& msg);
void CurrentPose(const turtlesim::Pose::ConstPtr& msg);

// global variables
bool STOP = true;
geometry_msgs::Twist	VEL;
turtlesim::Pose		CURRENT; 
geometry_msgs::Pose2D	DESIRED;

int main(int argc, char **argv)
{ 
   double	cVal;
 
   // assigns the constant for the controller
   cout << "What constant value would you like? "; 
   cin >> cVal;
   
   cout << cVal << endl;
   
   // runs roscore
   ros::init(argc, argv, "squirtle_use_surf");
   
   // node object declaration
   ros::NodeHandle n;
   
   // Subscriber to obtain desired position commands   
   ros::Subscriber DesPose_sub = n.subscribe("/turtle1/PositionCommand", 5, DesiredPose);
   
   // Subscriber to obtain current position
   ros::Subscriber CurPose_sub = n.subscribe("/turtle1/pose", 5, CurrentPose);
   
   // Publisher to send command velocity
   ros::Publisher Twist_pub = n.advertise<geometry_msgs::Twist>("/turtle1/cmd_vel", 100);
   
   // Loop Frequency (Hz)
   ros::Rate rate(15);
   
   ROS_INFO("Ready to send position commands");
   while (ros::ok() && n.ok())
   {
         ros::spinOnce();
         if (STOP = false)
         {
               cout << "Processing...\n";
               Twist_pub.publish(VEL);
         }
         else
         {
               cout << "Waiting...\n";
         }
         rate.sleep();
   }
}   
   
   
   
   // checks for incoming messages
 //  ros::spin();
  
   

void DesiredPose(const geometry_msgs::Pose2D::ConstPtr& msg)
{
   STOP = false;
   DESIRED.x = msg->x;
   DESIRED.y = msg->y;
   VEL.angular += 1;
   return;
}

void CurrentPose(const turtlesim::Pose::ConstPtr& msg)
{
   CURRENT.x = msg->x;
   CURRENT.y = msg->y;
   CURRENT.theta = msg->theta;
   return;
}