#include <iostream>
#include "ros/ros.h"
#include "geometry_msgs/Twist.h"
#include "geometry_msgs/Pose2D.h"
using namespace std;

void Pose();

int main(int argc, char **argv)
{
  double	d0;
  
  ros::init(argc, argv, "squirtle_use_surf_control");
  
  ros::NodeHandle n;


  
  cout << "Where would you like to go? \n";
  cin >> d0; 

  // Subscribes to robot's position
  ros::Subscriber Pose_sub = n.subscribe("Pose", 100, Pose);
  
  // Publishes robot's velocity
  ros::Publisher Velocity_pub = n.advertise<geometry_msgs::Twist>("Velocity", 100);

  
  //Loop rate
  ros::Rate rate(10);
  
}

void speed()
{
  error = Pose - d0;
  speed = k * error;      
  Velocity_pub.publish(speed);
}