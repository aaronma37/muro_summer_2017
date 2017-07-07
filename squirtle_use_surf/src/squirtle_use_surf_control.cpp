#include <iostream>
#include "ros/ros.h"
//#include "geometry_msgs/Twist.h"
//#include "geometry_msgs/Pose.h"
#include "squirtle_use_surf/Robot.h"
#include "squirtle_use_surf/Control.h"
using namespace std;

// function prototypes
void Speed();
double Error();
void CurrPose(const squirtle_use_surf::Robot::ConstPtr& msg);
squirtle_use_surf::Control VELOCITY;
squirtle_use_surf::Robot   CURRENT;
bool first;
// global variables
ros::Subscriber Pose_sub;
ros::Publisher  Velocity_pub;
double 		d0;
double		k;
int main(int argc, char **argv)
{
  // runs roscore
  ros::init(argc, argv, "squirtle_use_surf_control");
  
  // node object declaration 
  ros::NodeHandle n;
  
  // prompts user for a desired position
  cout << "Where would you like to go? ";
  cin >> d0; 
  
  // prompts user for a proportionality constant  
  cout << "Enter a constant: ";
  cin >> k; 

  // Subscribes to robot's position
  Pose_sub = n.subscribe("Pose", 100, CurrPose);
  
  // Publishes robot's velocity
  Velocity_pub = n.advertise<squirtle_use_surf::Control>("Velocity", 100);

  // Loop rate
  ros::Rate rate(10);
  
  ROS_INFO("Ready to send speed");
  while(ros::ok())
    {
    // calculates the speed to be published
    Speed();
    ros::spinOnce();
    rate.sleep();
    }
  
  return 0;	
}

void Speed()
{	
  double errorVal;
  double speed;
  
   if(first)
	{
	VELOCITY.u = 0;
        CURRENT.x = 0;
        first = false;
        }
  // calls the Error function and catches the return value
  errorVal = d0 - CURRENT.x;
  cout << errorVal << endl;
  
  // calculates the speed based on the velocity
  speed = k * errorVal;      
  VELOCITY.u = speed;
  // displays speed
  cout << speed << endl;
  
  // publishes the speed to the Velocity topic
  Velocity_pub.publish(VELOCITY);
}

 void CurrPose(const squirtle_use_surf::Robot::ConstPtr& msg)
 {
  CURRENT.x = msg -> x;
 }

