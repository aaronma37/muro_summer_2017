#include "ros/ros.h"
#include "geometry_msgs/Twist.h"
ros::Publisher velocity_publisher;
using namespace std;

void move(double speed, double distance, bool isForward);

int main(int argc, char **argv)
{
 
 
 ros::init(argc, argv, "squirtle_use_surf");
 ros::NodeHandle n;
 geometry_msgs::Twist vel_msg;
 velocity_publisher = n.advertise<geometry_msgs::Twist>("/turtle1/cmd_vel", 10);
 
 cout << "What constant  
 move(
 
 void move(double speed, double distance, bool isForward)
 {
     geometry_msgs::Twist vel_msg;
     vel_msg.linear.x = abs
     double t0 = ros::Time::now().toSec();
     double current_distance = 0;
     ros::Rate loop_rate(10);
     do
       {
          velocity_publisher.publish(vel_msg);
          double t1=ros::Time::now().toSec(t1 - t0);
          ros::spinOnce();
          loop_rate.sleep();
       }while (current_distance < distance);
    
         vel_msg.linear.x = abs(speed);
     // current time (t(0))
     // publish the velocity
         
 }       