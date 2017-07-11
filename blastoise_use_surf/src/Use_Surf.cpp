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
turtlesim::Pose POSE;
geometry_msgs::Twist VEL;

double      DEST;
double      CURRENT;
int main (int argc, char **argv)
{
    // starts the node
    ros::init(argc, argv, "Use_Surf");

    // creates the node object
    ros::NodeHandle n;
    
    // prompts user for the corresponding destination
    cout << "What is your reference value? ";
    cin >> DEST;

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
	CURRENT = POSE.x - 5.5;
        cout << "Position: " << CURRENT << endl;
}

void Speed()
{
        double      speed;
        speed = 0.2 * (DEST - CURRENT);
        VEL.linear.x = speed;
        VEL_PUB.publish(VEL);
        cout << "Velocity: " << speed << endl ;
}
