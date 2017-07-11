#include "ros/ros.h"
#include <cmath>
#include <iostream>
#include "turtlesim/Pose.h"
#include "geometry_msgs/Twist.h"
using namespace std;

// function prototypes
void PoseCallback(const turtlesim::Pose::ConstPtr& msg);
void C_Movement1();
void C_Movement2();
void C_Movement3();
void C_Movement4();
void C_Movement5();

// global variables
bool STOP = true;
ros::Publisher VEL_PUB;
ros::Subscriber POSE_SUB;
turtlesim::Pose POSE;
geometry_msgs::Twist VEL;

int main(int argc, char **argv)
{
        ros::init(argc, argv, "Initials1");
                
        ros::NodeHandle n;
        
        POSE_SUB = n.subscribe("Blastoise/pose",1000,PoseCallback);
        VEL_PUB = n.advertise<geometry_msgs::Twist>("/Blastoise/cmd_vel", 1000);
        
        
        ros::Rate rate(10);     
        
        // the first movement 
        while((ros::ok()) && (STOP))
                {
                ros::spinOnce();
                C_Movement1();
                VEL_PUB.publish(VEL);
                rate.sleep();

                if (POSE.x == .25)                
                        {
                        STOP = false;
                        cout << "STOP \n";
                        }
          
                }
                   STOP = true;

        while((ros::ok()) && (STOP))
                {
                ros::spinOnce();
                cout << POSE.theta << endl;
                C_Movement2();
                VEL_PUB.publish(VEL);
                rate.sleep();

                if (POSE.theta > 4.709)                
                        {
                        STOP = false;
                        cout << "STOP \n";
                        }
                }

                  STOP = true;

        while((ros::ok()) && (STOP))
                {
                ros::spinOnce();
                C_Movement3();
                VEL_PUB.publish(VEL);
                rate.sleep();

                if (POSE.y < 3.26)                
                        {
                        STOP = false;
                        cout << "STOP \n";
                        }
          
                }
                   STOP = true;

        while((ros::ok()) && (STOP))
                {
                ros::spinOnce();
                cout << POSE.theta << endl;
                C_Movement4();
                VEL_PUB.publish(VEL);
                rate.sleep();

                if (POSE.theta > 5.49)                
                        {
                        STOP = false;
                        cout << "STOP \n";
                        }
                }

                  STOP = true;

        while((ros::ok()) && (STOP))
                {
                ros::spinOnce();
                C_Movement5();
                VEL_PUB.publish(VEL);
                rate.sleep();

                if (POSE.x == 2.5)                
                        {
                        STOP = false;
                        cout << "STOP \n";
                        }
          
                }

        return 0;
}

void PoseCallback(const turtlesim::Pose::ConstPtr& msg)
{
        POSE.x = msg -> x;
        POSE.y = msg -> y;
        POSE.theta = msg -> theta;
       
        cout << "X : " << POSE.x << " Y: " << POSE.y << " theta: " << POSE.theta << endl;
}

void C_Movement1()
{
        
        VEL.linear.x = 0.9 * (POSE.x - 0.25);

        cout << "V: " << VEL.linear.x << endl; 
        VEL.linear.y = 0;
        VEL.linear.z = 0;
        VEL.angular.x = 0;
        VEL.angular.y = 0;
        VEL.angular.z = 0;
}

void C_Movement2()
{
        
        VEL.linear.x = 0;
        VEL.linear.y = 0;
        VEL.linear.z = 0;
        VEL.angular.x = 0;
        VEL.angular.y = 0;
        VEL.angular.z = .9 * (4.71 - POSE.theta);
        cout << "A: " << VEL.angular.z << endl;
}

void C_Movement3()
{
        
        VEL.linear.x = 0.9 * (POSE.y - 3.26);
        VEL.linear.y = 0;
        VEL.linear.z = 0;
        VEL.angular.x = 0;
        VEL.angular.y = 0;
        VEL.angular.z = 0;
        cout << "V: " << VEL.linear.y << endl;
}

void C_Movement4()
{
        
        VEL.linear.x = 0;
        VEL.linear.y = 0;
        VEL.linear.z = 0;
        VEL.angular.x = 0;
        VEL.angular.y = 0;
        VEL.angular.z = .9 * (5.55 - POSE.theta);
        cout << "A: " << VEL.angular.z << endl;
}

void C_Movement5()
{
        
        VEL.linear.x = 0.9 * (2.5 - POSE.x);

        cout << "V: " << VEL.linear.x << endl; 
        VEL.linear.y = 0;
        VEL.linear.z = 0;
        VEL.angular.x = 0;
        VEL.angular.y = 0;
        VEL.angular.z = 0;
}