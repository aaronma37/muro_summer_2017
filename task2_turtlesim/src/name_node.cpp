#include "ros/ros.h"
#include <sstream>
#include "geometry_msgs/Twist.h"
#include "turtlesim/Pose.h"
#include "turtlesim/Spawn.h"
using namespace std; 

// TURTLE 1 
turtlesim::Pose T_Actual_Pose;
turtlesim::Pose O_Actual_Pose;
turtlesim::Pose M_Actual_Pose;
turtlesim::Pose M2_Actual_Pose;

turtlesim::Spawn srv;
ros::ServiceClient add_turtle;

ros::Publisher Tposition_publisher; 
ros::Subscriber Tposition_subscriber;

ros::Publisher Oposition_publisher; 
ros::Subscriber Oposition_subscriber;

ros::Publisher Mposition_publisher;
ros::Subscriber Mposition_subscriber;

ros::Publisher M2position_publisher;
ros::Subscriber M2position_subscriber;

void TpositionCallback(const turtlesim::Pose::ConstPtr & T_position_msg){
	// global variables that allow the updated position to be used working with pointers
	T_Actual_Pose.x=T_position_msg->x;
	T_Actual_Pose.y=T_position_msg->y;
	T_Actual_Pose.theta=T_position_msg->theta;

}

void OpositionCallback(const turtlesim::Pose::ConstPtr & O_position_msg){
	// global variables that allow the updated position to be used working with pointers
	O_Actual_Pose.x=O_position_msg->x;
	O_Actual_Pose.y=O_position_msg->y;
	O_Actual_Pose.theta=O_position_msg->theta;
}

void MpositionCallback(const turtlesim::Pose::ConstPtr & M_position_msg){
	// global variables that allow the updated position to be used working with pointers
	M_Actual_Pose.x=M_position_msg->x;
	M_Actual_Pose.y=M_position_msg->y;
	M_Actual_Pose.theta=M_position_msg->theta;
}

void M2positionCallback(const turtlesim::Pose::ConstPtr & M2_position_msg){
	// global variables that allow the updated position to be used working with pointers
	M2_Actual_Pose.x=M2_position_msg->x;
	M2_Actual_Pose.y=M2_position_msg->y;
	M2_Actual_Pose.theta=M2_position_msg->theta;
}


// function distanceToGoal uses the pathagoream theorem to find the distance between 
// the postion of the robot and the goal postion


double distanceToGoal(double x, double y, double x_goal, double y_goal){
	double C = sqrt(pow((x_goal-x),2) + pow((y_goal-y),2)); 
	return C; 
}

void robo_rotate(turtlesim::Pose goal_position){
	geometry_msgs::Twist angular_msg;

	ros::Rate loop_rate(1000);
	do{	angular_msg.angular.z = goal_position.theta - T_Actual_Pose.theta;
		angular_msg.linear.x = 0; 
		Tposition_publisher.publish(angular_msg); 
		loop_rate.sleep();
		ros::spinOnce();
	}while(goal_position.theta > T_Actual_Pose.theta);
	angular_msg.linear.x = 0;
	angular_msg.angular.z = 0; 
	Tposition_publisher.publish(angular_msg); 
}

// function robo_move where the user decides the goal distance and k
void robo_move(turtlesim::Pose goal_position, double k){
	geometry_msgs::Twist linear_msg; // msg that will tell the
	// robot to move to the location desired 
 	linear_msg.linear.x = k*distanceToGoal(T_Actual_Pose.x, T_Actual_Pose.y, goal_position.x, goal_position.y);
		// this is simply u = k(xgoal-x)
	linear_msg.angular.z = 0;
		// angle between the orientation of the turtle and the goal postion
	double t_initial = ros::Time::now().toSec();
	double actual_distance = 0.0;
	ros::Rate loop_rate(1000);
	do{	Tposition_publisher.publish(linear_msg); //publishes the message to the robot
		double t_final = ros::Time::now().toSec(); 
		actual_distance = linear_msg.linear.x * (t_final-t_initial);
		loop_rate.sleep();
		ros::spinOnce();
	}while(actual_distance<(linear_msg.linear.x/k)); // repeat until it gets within 0.5 units
	linear_msg.linear.x = 0; // forces the robot to stop moving 
	linear_msg.angular.z = 0;
	Tposition_publisher.publish(linear_msg); // publishes the messages to the turtlebot
}

// Fucntions to make the O
void robo_makeO(turtlesim::Pose goal_position, double k){
	geometry_msgs::Twist u_msg; // msg that will tell the
	// robot to move to the location desired 
	ros::Rate loop_rate(1000); // rate of how many messages are sent
	double t_t = ros::Time::now().toSec();
	double angular_distance = 0;
	do{ u_msg.linear.x = k*distanceToGoal(0, 0, goal_position.x, goal_position.y);
		// this is simply u = k(xgoal-x)
		u_msg.angular.z = atan2(goal_position.y-0, goal_position.x-0);
		// angle between the orientation of the turtle and the goal postion
		double t_top = ros::Time::now().toSec();
		angular_distance = u_msg.linear.x *(t_top-t_t);
		Oposition_publisher.publish(u_msg); //publishes the message to the robot 
		loop_rate.sleep();
		ros::spinOnce();
	
	}while(angular_distance <= 8) ; // repeat until it gets within 0.5 units

	u_msg.linear.x = 0; // forces the robot to stop moving 
	u_msg.angular.z = 0;
	Oposition_publisher.publish(u_msg); // publishes the messages to the turtlebot
}

void robo_rotateM(turtlesim::Pose goal_position){
	geometry_msgs::Twist angular_msg;

	ros::Rate loop_rate(100); 
	do{	angular_msg.angular.z = goal_position.theta - M_Actual_Pose.theta;
		angular_msg.linear.x = 0; 
		Mposition_publisher.publish(angular_msg); 
		loop_rate.sleep();
		ros::spinOnce();
	}while(goal_position.theta > M_Actual_Pose.theta);
	angular_msg.linear.x = 0;
	angular_msg.angular.z = 0; 
	Mposition_publisher.publish(angular_msg);
}

// function robo_move where the user decides the goal distance and k
void robo_moveM(turtlesim::Pose goal_position, double k){
	geometry_msgs::Twist linear_msg; // msg that will tell the
	// robot to move to the location desired 
 	linear_msg.linear.x = k*distanceToGoal(M_Actual_Pose.x, M_Actual_Pose.y, goal_position.x, goal_position.y);
		// this is simply u = k(xgoal-x)
	linear_msg.angular.z = 0;
		// angle between the orientation of the turtle and the goal postion
	double t_initial = ros::Time::now().toSec();
	double actual_distance = 0.0;
	ros::Rate loop_rate(1000);
	do{	Mposition_publisher.publish(linear_msg); //publishes the message to the robot
		double t_final = ros::Time::now().toSec(); 
		actual_distance = linear_msg.linear.x * (t_final-t_initial);
		loop_rate.sleep();
		ros::spinOnce();
	}while(actual_distance<(linear_msg.linear.x/k)); // repeat until it gets within 0.5 units
	linear_msg.linear.x = 0; // forces the robot to stop moving 
	linear_msg.angular.z = 0;
	Mposition_publisher.publish(linear_msg); // publishes the messages to the turtlebot
}

void robo_rotateM2(turtlesim::Pose goal_position){
	geometry_msgs::Twist angular_msg;

	ros::Rate loop_rate(100); 
	do{	angular_msg.angular.z = goal_position.theta - M2_Actual_Pose.theta;
		angular_msg.linear.x = 0; 
		M2position_publisher.publish(angular_msg); 
		loop_rate.sleep();
		ros::spinOnce();
	}while(goal_position.theta > M2_Actual_Pose.theta);
	angular_msg.linear.x = 0;
	angular_msg.angular.z = 0; 
	M2position_publisher.publish(angular_msg);
}

// function robo_move where the user decides the goal distance and k
void robo_moveM2(turtlesim::Pose goal_position, double k){
	geometry_msgs::Twist linear_msg; // msg that will tell the
	// robot to move to the location desired 
 	linear_msg.linear.x = k*distanceToGoal(M2_Actual_Pose.x, M2_Actual_Pose.y, goal_position.x, goal_position.y);
		// this is simply u = k(xgoal-x)
	linear_msg.angular.z = 0;
		// angle between the orientation of the turtle and the goal postion
	double t_initial = ros::Time::now().toSec();
	double actual_distance = 0.0;
	ros::Rate loop_rate(1000);
	do{	M2position_publisher.publish(linear_msg); //publishes the message to the robot
		double t_final = ros::Time::now().toSec(); 
		actual_distance = linear_msg.linear.x * (t_final-t_initial);
		loop_rate.sleep();
		ros::spinOnce();
	}while(actual_distance<(linear_msg.linear.x/k)); // repeat until it gets within 0.5 units
	linear_msg.linear.x = 0; // forces the robot to stop moving 
	linear_msg.angular.z = 0;
	M2position_publisher.publish(linear_msg); // publishes the messages to the turtlebot
}

int main(int argc, char **argv)
{
	ros::init(argc,argv,"name_node"); 
	ros::NodeHandle n;
	add_turtle = n.serviceClient<turtlesim::Spawn>("spawn");
	srv.request.x = 2.544445;
	srv.request.y = 5.544445;
	srv.request.theta = 0; 
	srv.request.name = "turtle2"; 
	add_turtle.call(srv);

	add_turtle = n.serviceClient<turtlesim::Spawn>("spawn");
	srv.request.x = 7.544445;
	srv.request.y = 5.544445;
	srv.request.theta = 0; 
	srv.request.name = "turtle3"; 
	add_turtle.call(srv);

	add_turtle = n.serviceClient<turtlesim::Spawn>("spawn");
	srv.request.x = 9.544445;
	srv.request.y = 5.544445;
	srv.request.theta = 0; 
	srv.request.name = "turtle4"; 
	add_turtle.call(srv);


	Tposition_publisher = n.advertise<geometry_msgs::Twist>("/turtle2/cmd_vel",1000);
	// publisher to be able to publis messages in order to move the obot
	Tposition_subscriber = n.subscribe("/turtle2/pose",100,TpositionCallback); 
	// subscriber in order to know the actual position of the robot

	Oposition_publisher = n.advertise<geometry_msgs::Twist>("/turtle1/cmd_vel",1000);
	// publisher to be able to publis messages in order to move the obot
	Oposition_subscriber = n.subscribe("/turtle1/pose",100,OpositionCallback); 

	Mposition_publisher = n.advertise<geometry_msgs::Twist>("/turtle3/cmd_vel",1000);
	// publisher to be able to publis messages in order to move the obot
	Mposition_subscriber = n.subscribe("/turtle3/pose",100,MpositionCallback); 

	M2position_publisher = n.advertise<geometry_msgs::Twist>("/turtle4/cmd_vel",1000);
	// publisher to be able to publis messages in order to move the obot
	M2position_subscriber = n.subscribe("/turtle4/pose",100,M2positionCallback);

	ros::Rate loop_rate(1000);
	// takes the input and moves the robot to that location

	//MAKING THE T 
	turtlesim::Pose goal_position;
	goal_position.x = 2.544445;
	goal_position.y = 8; 
	goal_position.theta = 3.14159265/2;
	robo_rotate(goal_position);
	robo_move(goal_position, 0.5); //k = 0.
	
	turtlesim::Pose goal_position2;
	goal_position2.x = 1.544445;
	goal_position2.y = 8;
	goal_position2.theta = 3.14159265;
	robo_rotate(goal_position2);
	robo_move(goal_position2, 0.5);

	turtlesim::Pose goal_position3;
	goal_position3.x = 3.544445;
	goal_position3.y = 8;
	goal_position3.theta = 2*3.14159265; 
	robo_rotate(goal_position3);
	robo_move(goal_position3, 0.5);

	//MAKING THE O
	turtlesim::Pose O_position1;
	O_position1.x = 1.4;
	O_position1.y = 1.4; 
	robo_makeO(O_position1, 0.5);

	//MAKING THE M 
	turtlesim::Pose M_position;
	M_position.x = 7.544445;
	M_position.y = 8; 
	M_position.theta = 3.14159265/2;
	robo_rotateM(M_position);
	robo_moveM(M_position, 0.5); //k = 0.5

	turtlesim::Pose M_position2;
	M_position2.x = 8.544445;
	M_position2.y = 6.772222; 
	M_position2.theta = (7)*3.14159265/4;
	robo_rotateM(M_position2);
	robo_moveM(M_position2, 0.5); //k = 0.5

	turtlesim::Pose M2_position;
	M2_position.x = 9.544445;
	M2_position.y = 8; 
	M2_position.theta = 3.14159265/2;
	robo_rotateM2(M2_position);
	robo_moveM2(M2_position, 0.5); //k = 0.5

	turtlesim::Pose M2_position2;
	M2_position2.x = 8.544445;
	M2_position2.y = 6.772222; 
	M2_position2.theta = (5)*3.14159265/4;
	robo_rotateM2(M2_position2);
	robo_moveM2(M2_position2, 0.5); //k = 0.5


	loop_rate.sleep();
	ros::spin();

	return 0;
}