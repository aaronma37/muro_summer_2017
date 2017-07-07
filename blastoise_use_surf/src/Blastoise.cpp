#include "ros/ros.h"
#include "geometry_msgs/Twist.h"
#include "turtlesim/Pose.h"
#include <iostream>
using namespace std;

// function prototypes
void VelocityCallback(const geometry_msgs::Twist::ConstPtr& msg);

// global variable
geometry_msgs::Twist VEL;
turtlesim::Pose POSE;
ros::Publisher POSE_PUB;
ros::Subscriber VEL_SUB;

int main(int argc, char **argv)
{
        // creates the node
        ros::init(argc, argv, "Blastoise");
        
        // creates the node object
        ros::NodeHandle n;

        // subscribes to the cmd_vel topic
        VEL_SUB = n.subscribe("/turtle1/cmd_vel", 1000, VelocityCallback);

        // publishes the position to the pose topic
        POSE_PUB = n.advertise<turtlesim::Pose>("/turtle1/pose", 1000);

        // loop frequency (Hz)
        ros::Rate rate(10);

        // receives callback and moves robot
        while (ros::ok())
        {
        POSE_PUB.publish(POSE);    
        cout << "Current Position: " << POSE.x << endl;
        ros::spinOnce();
        rate.sleep();
        }

}

void VelocityCallBack(const geometry_msgs::Twist::ConstPtr& msg)
{
        double speed;
        speed = msg -> linear.x;
        VEL.linear.x = speed;
        cout << "Velocity" << speed << endl;
}