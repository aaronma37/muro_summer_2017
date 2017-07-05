#!/usr/bin/env python

import rospy
from test_1.msg import Control
from test_1.msg import Pose

class controller():

    def __init__(self):
        #create the Robot node
        rospy.init_node('control_sys',anonymous=True)
        #create the publisher, topic name and object
        self.control_pub = rospy.Publisher('ctrl_topic', Control, queue_size=10)
        #create the subscriber
        self.pose_sub = rospy.Subscriber('pose_topic', Pose, self.callback)
        self.pose = Pose()
        #define the loop frequency rate of 10 Hz
        self.rate = rospy.Rate(10)
#storage data every incoming message
    def callback(self,data):
        self.pose = data
        self.pose.x = round(self.pose.x, 4)
#compute controller value
    def run_controller(self):
        #create Pose instance and get the reference value
        ref_pose = Pose()
        ref_pose.x = input("set x reference value:")
        #set the tolerance to stop the ctrl_val loop
        tolerance = 0.0005
        #set proportional gain value
        kp = 0.2
        #define ctrl_val instance
        ctrl_val = Control()
        ctrl_val.ref = ref_pose.x
        #ctrl_val loop running @ 10Hz
        while abs(ref_pose.x-self.pose.x) >= tolerance: #or (not rospy.is_shutdown()):
            #Compute ctrl_val
            ctrl_val.u = kp*(ref_pose.x-self.pose.x)
            #publish ctrl_val
            self.control_pub.publish(ctrl_val)
            rospy.loginfo("Actual U_value: %f" % (ctrl_val.u))
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
        u = controller()
        u.run_controller()
    except rospy.ROSInterruptException: pass
