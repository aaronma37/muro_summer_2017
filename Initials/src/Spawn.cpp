#include "ros/ros.h"
#include <iostream>
#include "turtlesim/Pose.h"
#include "geometry_msgs/Twist.h"
#include "turtlesim/Spawn.h"
using namespace std;

turtlesim::Spawn SPAWN;

int main(int argc, char **argv)
{
        ros::init(argc, argv, "Spawn");
                
        ros::NodeHandle n;
        
        ros::ServiceClient spawn = n.serviceClient<turtlesim::Spawn>("spawn");



        SPAWN.request.x = 11;
        SPAWN.request.y = 10;
        SPAWN.request.theta = 3.14;
        SPAWN.request.name = "Squirtle";
        spawn.call(SPAWN);
        
        SPAWN.request.x = 2.5;
        SPAWN.request.y = 10;
        SPAWN.request.theta = 3.93;
        SPAWN.request.name = "Blastoise";
        spawn.call(SPAWN);
        
        return 0;
}