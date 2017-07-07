#include "ros/ros.h"
#include "geometry_msgs/Twist.h"
#include "turtlesim/Pose.h"
#include <iostream>
using namespace std;


// function prototypes
void Speed();
void PoseCallback(const turtlesim::Pose::ConstPtr& msg);


//global variables
ros::Publisher VEL_PUB;
ros::Subscriber POSE_SUB;
geometry_msgs::Twist VEL;
turtlesim::Pose POSE;

double      CONST;
double      DEST;
int main (int argc, char **argv)
{
    // starts the node
    ros::init(argc, argv, "Use_Surf");

    // creates the node object
    ros::NodeHandle n;
    
    // prompts user for the corresponding destination
    cout << "What is your reference value? (BE SURE TO SET "BLASTOISE" COMMANDS FIRST) ";
    cin >> DEST;

    // prompts user for the corresponding proportionality constant
    cout << "What is your constant? ";
    cin >> CONST;

    // subscribes to the pose topic
    POSE_SUB = n.subscribe("/turtle1/pose", 1000, PoseCallback);

    // publishes to the cmd_vel topic
    VEL_PUB = n.advertise<geometry_msgs::Twist>("/turtle1/cmd_vel",1000);

    // loop frequency (Hz)
    ros::Rate rate(10);

    // receive callbacks, calculates & publishes velocity
    while(ros::ok())
        {
        Speed();
        ros::spinOnce();
        rate.sleep();
        }

    return 0;
}

void PoseCallback(const turtlesim::Pose::ConstPtr& msg)
{
        POSE.x = msg -> x;
        cout << "Position: " << POSE.x << endl;
}

void Speed()
{
        double      speed;
        speed = CONST * (DEST - POSE.x);
        VEL.linear.x = speed;
        VEL_PUB.publish(VEL);
        cout << "Velocity: " << speed;
}