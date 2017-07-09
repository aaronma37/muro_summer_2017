#include <iostream>
#include "ros/ros.h"
#include "geometry_msgs/Twist.h"
#include "turtlesim/Pose.h"
#include <math>
using namespace std;

// global variables
double y1;
double y2;
double x1;
double x2;
geometry_msgs::Twist VEL;
turtlesim::Pose      POSE;
ros::Subscriber      POSE_SUB;
ros::PUBLISHER       VEL_PUB;

// function prototypes
void PoseCallback(const turtlesim::Pose::ConstPtr& msg);
void Linear();
void Angular();

int int main(int argc, const char *argv[])
{
    ros::init(argc, argv, "Use_Surf");
    
    ros::NodeHandle n;

    ros::Rate rate(10);

    POSE_SUB = n.subscribe("/turtle1/pose",1000,PoseCallback);

    VEL_PUB = n.advertise<geometry_msgs::Twist>("/turtle1/cmd_vel",1000);

    while(ros::ok())
        {
        Linear();
        Angular();
        ros::SpinOnce();
        rate.sleep();
        }




    return 0;
}

void PoseCallback(const turtlesim::Pose::ConstPtr& msg)
{
        POSE.x = msg -> x;
        POSE.y = msg -> y;
        POSE.theta = msg -> theta;
        cout << "Position - x: " << POSE.x << "y: " << POSE.y << "z: " << POSE.z << endl;
}

void Linear()
{
        
}

