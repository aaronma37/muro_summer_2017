#include <iostream>
#include "ros/ros.h"
//#include "geometry_msgs/Pose.h"
//#include "geometry_msgs/Twist.h"
#include "squirtle_use_surf/Robot.h"
#include "squirtle_use_surf/Control.h"
using namespace std;

// function prototypes
void Velocity(const squirtle_use_surf::Control::ConstPtr& vel);

// global variables
ros::Subscriber Velocity_sub;
ros::Publisher Pose_pub;
double VELOCITY;

double CONSTANT;
double DISTANCE;
int main(int argc, char **argv)
{ 
   cout << "Constant: ";
   cin >> CONSTANT;

   cout << "Distance: ";
   cin >> DISTANCE;
   
   // runs roscore
   ros::init(argc, argv, "squirtle_use_surf_robot");
   
   // node object declaration
   ros::NodeHandle n;
   
   // Subscriber to move the robot
   ros::Subscriber Velocity_sub = n.subscribe("Velocity", 100, Velocity);
   
   // Publishes the robot's position
   ros::Publisher Pose_pub = n.advertise<squirtle_use_surf::Robot>("Pose", 100);
   
   // Loop Frequency (Hz)
   ros::Rate rate(10);
   
   while (ros::ok())
      {
      squirtle_use_surf::Robot msg;
      msg.x = DISTANCE - (VELOCITY/CONSTANT);
      Pose_pub.publish(msg);
      
      ros::spinOnce();
      rate.sleep();
      }
      
   return 0;      
}   
  
void Velocity(const squirtle_use_surf::Control::ConstPtr& vel)
{
  VELOCITY = vel -> u;
  cout << "Velocity: " << VELOCITY << endl;
}
