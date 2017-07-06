#!/usr/bin/env python
import sys 
import rospy
from muro_summer_2017.msg import controller
from muro_summer_2017.msg import def_pos_X
  
class robotics():

    def __init__(self):
        #creando nodo
        rospy.init_node('robotics_sys',anonymous=True)
        #create the publisher, topic name and object
        self.def_pos_X_pub = rospy.Publisher('pose_topic',def_pos_X,queue_size=10)
        #create the subscriber
        self.controller_sub = rospy.Subscriber('ctrl_topic',controller, self.callback)
        self.ctrl_val = controller()
        self.rate = rospy.Rate(10) #10 hz 
#storage data every incoming message
    def callback(self,data):
        self.ctrl_val = data
        self.ctrl_val.u = round(self.ctrl_val.u, 5)
        self.ctrl_val.x = round(self.ctrl_val.x, 5)
#compute controller value
    def run_robotics(self):
        #create Pose instance and get the reference value
        def_pos_X_val = def_pos_X()
        #create a historial position value
        xp=0;
        #ctrl_val loop running @ 10Hz
        while not rospy.is_shutdown():
            #Compute actual position
            def_pos_X_val.x= xp + self.ctrl_val.u
            #update the position
            self.def_pos_X_pub.publish(def_pos_X_val)
            rospy.loginfo("Actual x_position_value: %f" % (def_pos_X_val.x))
            #actual position is now the las position
            xp = def_pos_X_val.x
            self.rate.sleep()
        rospy.spin()
#main function
if __name__ == '__main__':
    try:
        #create the u instance and run the robot
        u = robotics()
        u.run_robotics()
    except rospy.ROSInterruptException: pass
