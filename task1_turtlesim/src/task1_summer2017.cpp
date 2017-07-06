#include "ros/ros.h"
#include <sstream>
#include "geometry_msgs/Twist.h"
#include "turtlesim/Pose.h"
using namespace std; 

turtlesim::Pose Actual_Pose;
ros::Publisher position_publisher; 
ros::Subscriber position_subscriber;


void positionCallback(const turtlesim::Pose::ConstPtr & position_msg){
	// global variables that allow the updated position to be used working with pointers
	Actual_Pose.x=position_msg->x;
	Actual_Pose.y=position_msg->y;
	Actual_Pose.theta=position_msg->theta;

}
// function distanceToGoal uses the pathagoream theorem to find the distance between 
// the postion of the robot and the goal postion
double distanceToGoal(double x, double y, double x_goal, double y_goal){
	double C = sqrt(pow((x_goal-x),2) + pow((y_goal-y),2)); 
	return C; 
}

// function robo_move where the user decides the goal distance and k
void robo_move(turtlesim::Pose goal_position, double k){
	geometry_msgs::Twist u_msg; // msg that will tell the
	// robot to move to the location desired 
	ros::Rate loop_rate(100); // rate of how many messages are sent
	do{ u_msg.linear.x = k*distanceToGoal(Actual_Pose.x, Actual_Pose.y, goal_position.x, goal_position.y);
		// this is simply u = k(xgoal-x)
		u_msg.angular.z = atan2(goal_position.y-Actual_Pose.y, goal_position.x-Actual_Pose.x) - Actual_Pose.theta;
		// angle between the orientation of the turtle and the goal postion
		position_publisher.publish(u_msg); //publishes the message to the robot
		cout << "The actual X position is: " << Actual_Pose.x << endl;
		cout << "the actual Y position is: " << Actual_Pose.y << endl; 
		ros::spinOnce();
		loop_rate.sleep();
	}while(distanceToGoal(Actual_Pose.x, Actual_Pose.y, goal_position.x, goal_position.y) >= 0.5); // repeat until it gets within 0.5 units

	u_msg.linear.x = 0; // forces the robot to stop moving 
	u_msg.angular.z = 0;
	cout << "Finished";
	position_publisher.publish(u_msg); // publishes the messages to the turtlebot
}


int main(int argc, char **argv)
{
	ros::init(argc,argv,"task1"); 
	ros::NodeHandle n;
	position_publisher = n.advertise<geometry_msgs::Twist>("/turtle1/cmd_vel",1000);
	// publisher to be able to publis messages in order to move the robot
	position_subscriber = n.subscribe("/turtle1/pose",10,positionCallback); 
	// subscriber in order to know the actual position of the robot
	ros::Rate loop_rate(100);
	double x_goal;
	double y_goal;
	// asks the user for the goal distance
	cout << "X Goal?" << endl; 
	cin >> x_goal; 
	cout << "Y Goal?" << endl;
	cin >> y_goal; 
	
	// takes the input and moves the robot to that location
	turtlesim::Pose goal_position;
	goal_position.x = x_goal;
	goal_position.y = y_goal; 
	goal_position.theta = 0;
	robo_move(goal_position, 0.5); //k = 0.01
	loop_rate.sleep()
	ros::spin();

	return 0;
}