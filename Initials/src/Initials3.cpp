#include "ros/ros.h"
#include <iostream>
#include "turtlesim/Pose.h"
#include "geometry_msgs/Twist.h"
#include "turtlesim/Spawn.h"
using namespace std;

void PoseCallback(const turtlesim::Pose::ConstPtr& msg);

ros::Publisher VEL_PUB;
ros::Subscriber POSE_SUB;
turtlesim::Spawn SPAWN;
turtlesim::Pose POSE;
geometry_msgs::Twist VEL;



int main(int argc, char **argv)
{
        ros::init(argc, argv, "Initial1");
                
        ros::NodeHandle n;
        
        ros::service::waitForService("spawn");
        ros::ServiceClient add_turtle = n.serviceClient<turtlesim::Spawn>("spawn");
        SPAWN.request.x = 4;
        SPAWN.request.y = 4;
        SPAWN.request.theta = 0;
        add_turtle.call(SPAWN);
        POSE_SUB = n.subscribe("/turtle1/pose",1000,PoseCallback);
        VEL_PUB = n.advertise<geometry_msgs::Twist>("/turtle1/cmd_vel", 1000);
        ros::Rate rate(10);
        
        while(ros::ok())
                {
                ros::spinOnce();
                rate.sleep();
                }
        return 0;
}

void PoseCallback(const turtlesim::Pose::ConstPtr& msg)
{
        POSE.x = msg -> x;
        POSE.y = msg -> y;
        POSE.theta = msg -> theta;
}



