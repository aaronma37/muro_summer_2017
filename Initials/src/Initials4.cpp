#include "ros/ros.h"
#include <cmath>
#include <iostream>
#include "turtlesim/Pose.h"
#include "geometry_msgs/Twist.h"
using namespace std;

void PoseCallback(const turtlesim::Pose::ConstPtr& msg);
void C_Movement1();
void C_Movement2();
void C_Movement3();
void C_Movement4();
void C_Movement5();
void C_Movement6();
void C_Movement7();
void C_Movement8();
void C_Movement9();
void C_Movement10();
void C_Movement11();

bool STOP = true;
ros::Publisher VEL_PUB;
ros::Subscriber POSE_SUB;
turtlesim::Pose POSE;
geometry_msgs::Twist VEL;

int main(int argc, char **argv)
{
        ros::init(argc, argv, "Initials4");
                
        ros::NodeHandle n;
        
        POSE_SUB = n.subscribe("Squirtle/pose",1000,PoseCallback);
        VEL_PUB = n.advertise<geometry_msgs::Twist>("/Squirtle/cmd_vel", 1000);
        
        
        ros::Rate rate(10);     

        while((ros::ok()) && (STOP))
                {
                ros::spinOnce();
                C_Movement1();
                VEL_PUB.publish(VEL);
                rate.sleep();

                if (POSE.x == 8)                
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

                if (POSE.y < 5.51)                
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

                if (POSE.theta > 6.28)                
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

                if (POSE.x == 11)                
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
                C_Movement6();
                VEL_PUB.publish(VEL);
                rate.sleep();

                if (POSE.theta < 4.711)                
                        {
                        STOP = false;
                        cout << "STOP \n";
                        }
                }

        STOP = true;

        while((ros::ok()) && (STOP))
                {
                ros::spinOnce();
                C_Movement7();
                VEL_PUB.publish(VEL);
                rate.sleep();

                if (POSE.x == 8)                
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
                C_Movement8();
                VEL_PUB.publish(VEL);
                rate.sleep();

                if (POSE.theta < 4.71)                
                        {
                        STOP = false;
                        cout << "STOP \n";
                        }
                }

        STOP = true;

        while((ros::ok()) && (STOP))
                {
                ros::spinOnce();
                C_Movement9();
                VEL_PUB.publish(VEL);
                rate.sleep();

                if (POSE.y < 1)                
                        {
                        STOP = false;
                        cout << "STOP \n";
                        }
          
                }
        
                while((ros::ok()) && (STOP))
                {
                ros::spinOnce();
                cout << POSE.theta << endl;
                C_Movement10();
                VEL_PUB.publish(VEL);
                rate.sleep();

                if (POSE.theta < 6.28)                
                        {
                        STOP = false;
                        cout << "STOP \n";
                        }
                }

        STOP = true;

        while((ros::ok()) && (STOP))
                {
                ros::spinOnce();
                C_Movement11();
                VEL_PUB.publish(VEL);
                rate.sleep();

                if (POSE.x == 11)                
                        {
                        STOP = false;
                        cout << "STOP \n";
                        }
               }

                   
        
        STOP = true;
                
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
        VEL.linear.x = 0.9 * (POSE.x - 8);

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
        
        VEL.linear.x = 0.9 * (POSE.y - 5.5);
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
        VEL.angular.z = .9 * (6.28 - POSE.theta);
        cout << "A: " << VEL.angular.z << endl;
}

void C_Movement5()
{
        
        VEL.linear.x = 0.9 * (11 - POSE.x);

        cout << "V: " << VEL.linear.x << endl; 
        VEL.linear.y = 0;
        VEL.linear.z = 0;
        VEL.angular.x = 0;
        VEL.angular.y = 0;
        VEL.angular.z = 0;
}

void C_Movement6()
{
        
        VEL.linear.x = 0;
        VEL.linear.y = 0;
        VEL.linear.z = 0;
        VEL.angular.x = 0;
        VEL.angular.y = 0;
        VEL.angular.z = .9 * (POSE.theta - 3.14);
        cout << "A: " << VEL.angular.z << endl;
}

void C_Movement7()
{
        
        VEL.linear.x = 0.9 * (POSE.x - 8);

        cout << "V: " << VEL.linear.x << endl; 
        VEL.linear.y = 0;
        VEL.linear.z = 0;
        VEL.angular.x = 0;
        VEL.angular.y = 0;
        VEL.angular.z = 0;
}

void C_Movement8()
{
        
        VEL.linear.x = 0;
        VEL.linear.y = 0;
        VEL.linear.z = 0;
        VEL.angular.x = 0;
        VEL.angular.y = 0;
        VEL.angular.z = .9 * (4.71 - POSE.theta);
        cout << "A: " << VEL.angular.z << endl;
}

void C_Movement9()
{
        
        VEL.linear.x = 0.9 * (POSE.y - 5.5);
        VEL.linear.y = 0;
        VEL.linear.z = 0;
        VEL.angular.x = 0;
        VEL.angular.y = 0;
        VEL.angular.z = 0;
        cout << "V: " << VEL.linear.y << endl;
}

void C_Movement10()
{
        
        VEL.linear.x = 0;
        VEL.linear.y = 0;
        VEL.linear.z = 0;
        VEL.angular.x = 0;
        VEL.angular.y = 0;
        VEL.angular.z = .9 * (6.28 - POSE.theta);
        cout << "A: " << VEL.angular.z << endl;
}

void C_Movement11()
{
        
        VEL.linear.x = 0.9 * (11 - POSE.x);

        cout << "V: " << VEL.linear.x << endl; 
        VEL.linear.y = 0;
        VEL.linear.z = 0;
        VEL.angular.x = 0;
        VEL.angular.y = 0;
        VEL.angular.z = 0;
}