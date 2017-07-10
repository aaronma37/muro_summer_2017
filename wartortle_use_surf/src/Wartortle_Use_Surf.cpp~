#include <iostream>
#include "ros/ros.h"
#include "geometry_msgs/Twist.h"
#include "turtlesim/Pose.h"
#include <cmath>
using namespace std;

// global variables
double Y1;
double Y2;
double X1;
double X2;
double LIN;
double ANG;
double KL;
double KA;
geometry_msgs::Twist VEL;
turtlesim::Pose      POSE;
ros::Subscriber      POSE_SUB;
ros::Publisher       VEL_PUB;

// function prototypes
void PoseCallback(const turtlesim::Pose::ConstPtr& msg);
void Realignment();
void Linear();
void Angular();

int main(int argc, char **argv)
{
    ros::init(argc, argv, "Wartortle_Use_Surf");
    
    ros::NodeHandle n;

    ros::Rate rate(10);

    POSE_SUB = n.subscribe("/turtle1/pose",1000,PoseCallback);

    VEL_PUB = n.advertise<geometry_msgs::Twist>("/turtle1/cmd_vel",1000);

    cout << "Where would you like to go? (Enter x-coordinates followed by y-coordinates) ";
    cin >> X2 >> Y2;
    cout << "(" << X2 << "," << Y2 << ")" << endl;

    cout << "What linear constant would you prefer? ";
    cin >> KL;

    cout << "What angular constant would you prefer? ";
    cin >> KA;

    while(ros::ok())
        {
        Realignment();
        Linear();
        Angular();
        VEL_PUB.publish(VEL);
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

void Realignment()
{
    X1 = POSE.x - 5.5;
    Y1 = POSE.y - 5.5;
    cout << "Position - x: " << X1 << " y: " << Y1 << " theta: " << POSE.theta << endl;
}

void Linear()
{
    LIN = sqrt(((Y2 - Y1)*(Y2 - Y1)) + ((X2 - X1)*(X2 - X1)));
    LIN = KL * LIN;
    VEL.linear.x = LIN;
    cout << "Linear Velocity: " << LIN << endl;
}

void Angular()
{
    ANG = atan(Y2/X2) - atan(Y1/X1);
    ANG = KA * ANG;
    VEL.angular.x = 0;
    VEL.angular.y = 0;
    VEL.angular.z = ANG;
    cout << "Angular Velocity: " << ANG << endl;
}

