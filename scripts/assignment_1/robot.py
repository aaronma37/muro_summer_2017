#!/usr/bin/env python

import rospy
from muro_summer_2017.msg import Control
from muro_summer_2017.msg import Pose

class robot():

    def __init__(self):
        #create the Robot node
        rospy.init_node('robot_sys',anonymous=True)
        #create the publisher, topic name and object
        self.pose_pub = rospy.Publisher('pose_topic', Pose, queue_size=10)
        #create the subscriber
        self.control_sub = rospy.Subscriber('ctrl_topic', Control, self.callback)
        self.ctrl_val = Control()
        #define the loop frequency rate of 10 Hz
        self.rate = rospy.Rate(10)
#storage data every incoming message
    def callback(self,data):
        self.ctrl_val = data
        self.ctrl_val.u = round(self.ctrl_val.u, 4)
        self.ctrl_val.ref = round(self.ctrl_val.ref, 4)
#compute controller value
    def run_robot(self):
        #create Pose instance and get the reference value
        pose_val = Pose()
        #create a historial position value
        xl=0;
        #ctrl_val loop running @ 10Hz
        while not rospy.is_shutdown():#abs(self.ctrl_val.ref-pose_val.x) >= tolerance: #(not rospy.is_shutdown()) or (ul != self.ctrl_val.u):
            #Compute actual position
            pose_val.x=xl+self.ctrl_val.u
            #update the position
            self.pose_pub.publish(pose_val)
            rospy.loginfo("Actual x_position_value: %f" % (pose_val.x))
            #actual position is now the las position
            xl=pose_val.x
            # keep running @ establish rate before
            self.rate.sleep()
#keep the node running until stop
        rospy.spin()
#main function
if __name__ == '__main__':
    try:
        #create the u instance and run the robot
        u = robot()
        u.run_robot()
    except rospy.ROSInterruptException: pass