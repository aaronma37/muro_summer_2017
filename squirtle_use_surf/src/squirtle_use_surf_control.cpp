#include <iostream>
#include "ros/ros.h"
#include "geometry_msgs/Twist.h"
#include "geometry_msgs/Pose2D.h"
using namespace std;

// function prototypes
void CurrPose(const geometry_msgs::Pose2D::ConstPtr& msg);
void Speed(geometry_msgs::Pose2D current);

// global variables
ros::Subscriber Pose_sub;
ros::Publisher  Velocity_pub;

int main(int argc, char **argv)
{
  double	d0;
  double	k;
  
  ros::init(argc, argv, "squirtle_use_surf_control");
  
  ros::NodeHandle n;
  
  cout << "Where would you like to go? \n";
  cin >> d0; 
  
  cout << "Choose a constant: ";
  cin >> k; 

  // Subscribes to robot's position
  ros::Subscriber Pose_sub = n.subscribe("Pose", 100, CurrPose);
  
  // Publishes robot's velocity
  ros::Publisher Velocity_pub = n.advertise<geometry_msgs::Twist>("Velocity", 100);

  // Loop rate
  ros::Rate rate(10);
  
  // calculates the speed to be published
  speed(CurrPose);
}

void Speed(geometry_msgs::Pose2D current)
{	
  double error;
  
  error = current.x - d0;
  cout << error << endl;
  speed = k * error;      
  Velocity_pub.publish(speed);
}


void CurrPose(const geometry_msgs::Pose2D::ConstPtr& msg)
{
  CurrPose.x = msg -> x;
  CurrPose.y = msg -> y;
  CurrPose.theta = msg -> theta;
} 