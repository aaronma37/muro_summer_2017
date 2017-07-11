#include "ros/ros.h"
#include <iostream>
#include "turtlesim/Pose.h"
#include "geometry_msgs/Twist.h"
using namespace std;

void PoseCallback(const turtlesim::Pose::ConstPtr& msg);

ros::Publisher VEL_PUB;
ros::Subscriber POSE_SUB;
turtlesim::Pose POSE;
geometry_msgs::Twist VEL;



int main(int argc, char **argv)
{
        ros::init(argc, argv, "Initials1");
                
        ros::NodeHandle n;
        
        POSE_SUB = n.subscribe("/turtle1/pose",1000,PoseCallback);
        VEL_PUB = n.advertise<geometry_msgs::Twist>("/turtle1/cmd_vel", 1000);
        
        
        ros::Rate rate(10);     

        while(ros::ok())
                {
                ros::spinOnce();
                rate.sleep();
                VEL.linear.x = -1;
                VEL_PUB.publish(VEL);
                    
                }
        return 0;
}

void PoseCallback(const turtlesim::Pose::ConstPtr& msg)
{
        POSE.x = msg -> x;
        POSE.y = msg -> y;
        POSE.theta = msg -> theta;
}

void C_Movement()
{
        
}

