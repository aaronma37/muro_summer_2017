#!/usr/bin/env python
import rospy
from geometry_msgs.msg import Twist
from turtlesim.msg import Pose
from math import pow,atan2,sqrt,pi

#This program moves a differential WMR robot to a specified coordinate in xy frame
#using a simple proportional controller for linear and angular velocity of the robot
#The theory of this controller is detailed in [1] and a python example is shown
# in http://wiki.ros.org/turtlesim/Tutorials/Go%20to%20Goal
#[1] Corke, P. (2011). Robotics, vision and control: fundamental algorithms in MATLAB (Vol. 73). Springer.

class robot_controller():

    #inizialitation method
    def __init__(self):
        #create the node
        rospy.init_node('RT_controller',anonymous = True)
        #create the publiser and identyfy the topic
        self.velocities_pub = rospy.Publisher('/turtle1/cmd_vel', Twist, queue_size = 10)
        #create the subscriber and identify the topic
        self.pose_sub = rospy.Subscriber('/turtle1/pose', Pose, self.callback)
        #create the generalized q coordinate vector
        self.q = Pose()
        #define the loop freq rate @ 10Hz
        self.rate = rospy.Rate(10)
        #define limit values of the robot
        self.steering_ang_limit = 3*pi/4
        self.lin_velocity_limit = 3
        self.d_tolerance = 0.005
        #define gains
        self.Kp_vel = 1.5
        self.Kp_theta = 3

    #update the q vector in every incomming message
    def callback (self,data):
        self.q = data
        self.q.x = round(self.q.x, 4) #gets x position
        self.q.y = round(self.q.y, 4) #gets y position
        self.q.theta = round(self.q.theta, 5) #gets angular position

    #computes the angular speed control signal
    def ang_speed_controller(self, qref):
        angular_vel = self.Kp_theta * (atan2(qref.y-self.q.y, qref.x-self.q.x)-self.q.theta)
        if angular_vel > self.steering_ang_limit:
            angular_vel = self.steering_ang_limit
        elif angular_vel < (-self.steering_ang_limit):
            angular_vel = -self.steering_ang_limit
        return angular_vel

    #computes the linear speed control signal
    def lin_speed_controller(self, qref):
        velocity = self.Kp_vel * (sqrt(pow((qref.x-self.q.x), 2)+pow((qref.y-self.q.y), 2)))
        #set the saturation values for linear speed
        if velocity > self.lin_velocity_limit:
            velocity = self.lin_velocity_limit
        elif velocity < (-self.lin_velocity_limit):
            velocity = -self.lin_velocity_limit
        #returns the computed velocity
        return velocity

    #moves the robot to a specified coordinate in xy frame
    def move_to_coordinate(self):
        qref = Pose()
        #intoduce the reference coordinate
        qref.x = input("Set x value:")
        qref.y = input("Set y value:")
        v_msg = Twist()
        #sets to zero all unused magnitudes
        v_msg.linear.y = 0
        v_msg.linear.z = 0
        v_msg.angular.x = 0
        v_msg.angular.y = 0
        #executes the controller while the distances from robot to set point is
        #greather than than the specifies tolerance
        while sqrt(pow((qref.x-self.q.x), 2)+pow((qref.y-self.q.y), 2))>self.d_tolerance:
            #obtains linear and angular velocities from the their controllers
            v_msg.linear.x = self.lin_speed_controller(qref)
            v_msg.angular.z = self.ang_speed_controller(qref)
            #publish the velocities
            self.velocities_pub.publish(v_msg)
            self.rate.sleep()
        #stops the robot when the point is reached
        v_msg.linear.x = 0
        v_msg.angular.z = 0
        self.velocities_pub.publish(v_msg)
        #the robot has reached the set point
        print "Done, press ctrl+c to close"
        rospy.spin()

#main function
if __name__ == '__main__':
    try:
        #create the robot instance and execute the program
        robot = robot_controller()
        robot.move_to_coordinate()
    except rospy.ROSInterruptException: pass
