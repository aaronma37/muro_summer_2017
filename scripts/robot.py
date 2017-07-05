#!/usr/bin/env python

import rospy
from test_1.msg import Control
from test_1.msg import Pose

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
        #ref_pose = Pose()
        #ref_pose.x = input("set x reference value:")
        #set the tolerance to stop the ctrl_val loop
        #tolerance = 0.1
        #set proportional gain value
        #kp = 0.2
        #define ctrl_val instance
        pose_val = Pose()
        xl=0;
        #ul = 0
        #tolerance = 0.0005
        #ctrl_val loop running @ 10Hz
        while not rospy.is_shutdown():#abs(self.ctrl_val.ref-pose_val.x) >= tolerance: #(not rospy.is_shutdown()) or (ul != self.ctrl_val.u):
            #Compute ctrl_val
            #ctrl_val.u = kp*(ref_pose.x-self.pose.x)
            #publish ctrl_val
            #if ul != self.ctrl_val.u:
            pose_val.x=xl+self.ctrl_val.u
            #else:
                #pose_val.x=xl
            self.pose_pub.publish(pose_val)
            rospy.loginfo("Actual x_position_value: %f" % (pose_val.x))
            xl=pose_val.x
            #ul=self.ctrl_val.u
            self.rate.sleep()
        # stops
        #ctrl_val.u=0
        #self.control_pub.publish(ctrl_val)
#keep the node running until stop
        rospy.spin()
#main function
if __name__ == '__main__':
    try:
        #create the u instance and run the controller
        u = robot()
        u.run_robot()
    except rospy.ROSInterruptException: pass