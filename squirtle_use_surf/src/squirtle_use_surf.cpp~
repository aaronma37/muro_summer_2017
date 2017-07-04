#include "ros/ros.h"
#include "geometry_msgs/Pose2D.h"
#include "turtlesim/Pose.h"
#include "turtlesim/Velocity.h"
ros::Publisher velocity_publisher;
using namespace std;

// function prototypes
void DesiredPose(const geometry_msgs::Pose2D::ConstPtr& msg);
void CurrentPose(const turtlesim::Pose::ConstPtr& msg);

int main(int argc, char **argv)
{ 
   double		cVal;
 
   // assigns the constant for the controller
   cout << "What constant would you like? "
   cin >> cVal;
   
   cout << cVal << endl;
   
   // connects to roscore
   ros::init(argc, argv, "squirtle_use_surf");
   
   // node object declaration
   ros::NodeHandle n;
   
   // Subscriber to obtain desired position commands   
   ros::Subscriber DesPose_sub = n.subscribe("/turtle1/PositionCommand", 5, DesiredPose);
   
   // Subscriber to obtain current position
   ros::Subscriber CurPose_sub = n.subscribe("/turtle1/pose", 5, CurrentPose);
   
   // Publisher to send command velocity
   ros::Publisher Twist_pub = n.advertise<turtlesim::Velocity>("/turtle1/command_velocity", 100);
   
   // checks for incoming messages
   ros::spin();
  
   
}

void DesiredPose(const geometry_msgs::Pose2D::ConstPtr& msg)
{
   STOP = false;
   DesPose.x = msg->x;
   DesPose.y = msg->y;
   CmdVel.angular += 1;
   return;
}

void CurrentPose(const turtlesim::Pose::ConstPtr& msg)
{
   CurPose.x = msg->x;
   CurPose.y = msg->y;
   CurPose.theta = msg->theta;
   return;
}