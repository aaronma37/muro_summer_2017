#!/usr/bin/env python
import sys
import rospy
from muro_summer_2017.msg import controller
from muro_summer_2017.msg import def_pos_X

class pose():

    def __init__(self):
        #create the Robot node
        rospy.init_node('pose_sys',anonymous=True)
        #create the publisher, topic name and object
        self.controller_pub = rospy.Publisher('ctrl_topic', controller, queue_size=10)
        #create the subscriber
        self.def_pos_X_sub = rospy.Subscriber('pose_topic',def_pos_X, self.callback)
        self.def_pos_X = def_pos_X()  
        self.rate = rospy.Rate(10)
#storage data every incoming message
    def callback(self,data):
        self.def_pos_X = data
        self.def_pos_X.x = round(self.def_pos_X.x, 5)
#compute controller value
    def run_pose(self):
        #create Pose instance and get the reference value
        ref_def_pos_X = def_pos_X()
        ref_def_pos_X.x = input("set x reference value:")
        #set the tolerance to stop the ctrl_val loop
        tolerance = 0.00050
        #set proportional gain value
        kp = 0.25
        #define ctrl_val instance
        ctrl_val = controller()
        ctrl_val.u = ref_def_pos_X.x
        #ctrl_val loop running @ 10Hz
        while abs(ref_def_pos_X.x-self.def_pos_X.x) >= tolerance: #or (not rospy.is_shutdown()):
            #Compute ctrl_val
            ctrl_val.u = kp*(ref_def_pos_X.x-self.def_pos_X.x)
            #publish ctrl_val
            self.controller_pub.publish(ctrl_val)
            rospy.loginfo("Actual U_value: %f" % (ctrl_val.u))
            self.rate.sleep()
            #force to stop the robot
            ctrl_val.u = 0
            self.controller_pub.publish(ctrl_val)
            #keep the node running until stop.
        rospy.spin()
#main function
if __name__ == '__main__':
    try:
        #create the u instance and run the posicion
        u = pose()
        u.run_pose()
    except rospy.ROSInterruptException: pass
