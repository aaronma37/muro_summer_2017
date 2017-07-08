#!/usr/bin/env python

import rospy
import turtlesim.srv
from geometry_msgs.msg import Twist
from turtlesim.msg import Pose
from math import pow, atan2, sqrt, pi

class robot():
    #initialization method
    def __init__(self, x, y, theta):
        #initial conditions of the robot
        self.x = x
        self.y = y
        self.theta = theta
        #limit values
        self.lin_velocity_limit = 3
        self.steering_ang_limit = pi
        self.d_tolerance = 0.1
        self.a_tolerance = 0.001
        #define porportional gains
        self.Kp_vel = 0.8
        self.Kp_theta = 5
        #generic flags
        self.flag = 0
        self.flag1 = 0
        #creates a turtlebot on the screen using services
        rospy.wait_for_service('spawn')
        spawner = rospy.ServiceProxy('spawn', turtlesim.srv.Spawn)
        #spawns a robot with initial conditions and returns its name
        robotName = spawner(x, y, theta, "")
        name = str(robotName)
        #creates the publisher and subscriber
        self.velocities_pub = rospy.Publisher('/' + str(name[6:]) + '/cmd_vel', Twist, queue_size=10)
        self.pose_sub = rospy.Subscriber('/' + str(name[6:]) + '/pose', Pose, self.callback)
        #create the generalized q coordinate vector
        self.q = Pose()

    #update the q vector in every incomming message
    def callback (self,data):
        #self.q = data
        #self.q.x = round(self.q.x, 4) #gets x position
        #self.q.y = round(self.q.y, 4) #gets y position
        #self.q.theta = round(self.q.theta, 5) #gets angular position
        #self.q = data
        self.q.x = round(data.x, 4) #gets x position
        self.q.y = round(data.y, 4) #gets y position
        self.q.theta = round(data.theta, 5) #gets angular position

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

    #moves to specific coordinate in the x y frame
    def goto_xy(self, x, y):
        qref = Pose()
        qref.x = float(x)
        qref.y = float(y)
        v_msg = Twist()
        #sets to zero all unused magnitudes
        v_msg.linear.y = 0
        v_msg.linear.z = 0
        v_msg.angular.x = 0
        v_msg.angular.y = 0
        #verify if the angle is reached
        if not self.flag:
            if abs(atan2(qref.y-self.q.y, qref.x-self.q.x)-self.q.theta)>self.a_tolerance:
                #compute the angular velocity
                v_msg.angular.z = self.ang_speed_controller(qref)
                v_msg.linear.x = 0
                self.velocities_pub.publish(v_msg)
                self.flag = 0
            else:
                self.flag = 1
                self.flag1 = 0

        #verify if the coordinate is reached
        if self.flag:
            if sqrt(pow((qref.x-self.q.x), 2)+pow((qref.y-self.q.y), 2)) > self.d_tolerance:
                #compute the linear velocity
                v_msg.linear.x = self.lin_speed_controller(qref)
                v_msg.angular.z = 0
                #publish the velocity messag
                self.velocities_pub.publish(v_msg)
                self.flag = 1
            else:
                #proces is done reset flag and set flag1
                self.flag = 0
                self.flag1 = 1
        #check if the process is done and retun its value
        if self.flag1:
            #reset flag1 when the process is done
            self.flag1 = 0
            self.flag = 0
            return 1
        else:
            return 0
            
    #stops the robot
    def stop(self):
        v_msg = Twist()
        v_msg.linear.x = 0
        v_msg.linear.y = 0
        v_msg.linear.z = 0
        v_msg.angular.x = 0
        v_msg.angular.y = 0
        v_msg.angular.z = 0
        self.flag = 0
        self.flag1 = 0
        self.velocities_pub.publish(v_msg)

if __name__ == '__main__':
    #kill the first robot from the simulator
    rospy.wait_for_service('kill')
    kill_robot = rospy.ServiceProxy('kill', turtlesim.srv.Kill)
    kill_robot("turtle1")
    #create the vecctor of coordinates for each letter
    #row 1 are the x, and row 2 are the y
    #example: R[0][0] = 2
    #and      R[1][0] = 8  results in (2,8) coordinate
    R = [[2,4,2,4],[8,6,5,4]]
    D = [[5,7,7,5],[8,7,5,4]]
    C = [[8,8,10],[4,8,8]]
    #counter values
    cont1 = 0
    cont2 = int(0)
    cont3 = int(0)
    #flag values for robots instances
    r1 =0
    r2 =0
    r3 =0
    #create the node 
    rospy.init_node('MRT_controller', anonymous = True)
    rate = rospy.Rate(10)
    #create robot instances and its initial position
    robot1 = robot(2, 4, pi/2) #this robot plots R
    robot2 = robot(5, 4, pi/2) #this robot plots D
    robot3 = robot(10, 4, pi/2) #this robot plots C
    #start the routine
    while not (r1 and r2  and r3 ):

        #val = robot1.goto_xy(R[0][cont1], R[1][cont1])
        if robot1.goto_xy(R[0][cont1], R[1][cont1]):
            cont1 += 1
            if cont1>3:
                cont1 = 3
                robot1.stop()
                r1 = 1
        if robot2.goto_xy(D[0][cont2], D[1][cont2]):
            cont2 += 1
            if cont2 > 3:
                cont2 = 3
                robot2.stop()
                r2 =1
        if robot3.goto_xy(C[0][cont3], C[1][cont3]):
            cont3 += 1
            if cont3 > 2:
                cont3 = 2
                robot3.stop()
                r3 =1       
        rate.sleep()
    #finish message
    print "Done! press ctrl+c to finish"
    rospy.spin()