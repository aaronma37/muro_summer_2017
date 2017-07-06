#include <iostream>
#include "ros/ros.h"
#include "geometry_msgs/Twist.h"
#include "geometry_msgs/Pose.h"
using namespace std;

// function prototypes
void Speed();
double Error();
void CurrPose(const geometry_msgs::Pose::ConstPtr& msg);

// global variables
ros::Subscriber Pose_sub;
ros::Publisher  Velocity_pub;
double 		d0;
double		k;
geometry_msgs::Pose CURRENT;
geometry_msgs::Twist VELOCITY;
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
  ros::Subscriber Pose_sub = n.subscribe("Pose", 100, CurrPose);
  
  // Publishes robot's velocity
  ros::Publisher Velocity_pub = n.advertise<geometry_msgs::Twist>("Velocity", 100);

  // Loop rate
  ros::Rate rate(10);
  
  ROS_INFO("Ready to send speed");
  while(ros::ok())
    {
    ros::spinOnce();
    
    // calculates the speed to be published
    Speed();
    rate.sleep();
    }
  
  return 0;	
}

void Speed()
{	
  double errorVal;
  double speed;
  
  // calls the Error function and catches the return value
  errorVal = CURRENT.x - d0;
  cout << errorVal << endl;
  
  // calculates the speed based on the velocity
  speed = k * errorVal;      
  VELOCITY.linear.x = speed;
  // displays speed
  cout << speed << endl;
  
  // publishes the speed to the Velocity topic
  Velocity_pub.publish(VELOCITY);
}

void CurrPose(const geometry_msgs::Pose::ConstPtr& msg)
{
  CURRENT.x = msg -> x;
  CURRENT.y = msg -> y;
  CURRENT.theta = msg -> theta;
  
}

