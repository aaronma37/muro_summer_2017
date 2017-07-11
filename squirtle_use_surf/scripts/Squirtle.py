#!/usr/bin/env python
import rospy
from geometry_msgs.msg import Twist
from turtlesim.msg import Pose



def callback(data):
   pose.x = data.x
   pose.y = data.y
   pose.theta = data.theta
   

def __init__():
    rospy.init_node('Use_Surf', anonymous=True)
    sub = rospy.Subscriber("/turtle1/pose", Pose, callback)
    
    pub = rospy.Publisher('/turtle1/cmd_vel', Twist, queue_size = 10)
    global pose
    pose = Pose()
    rate = rospy.Rate(10)
    while not rospy.is_shutdown():
        global Err
        Err = 0.2 * (11 - pose.x)
        VEL = Twist()
        VEL.linear.x = Err
        VEL.linear.y = 0
        VEL.linear.z = 0

        VEL.angular.x = 0
        VEL.angular.y = 0
        VEL.angular.z = 0
        rospy.loginfo(VEL)
        rospy.loginfo(pose)
        pub.publish(VEL)
        rate.sleep
        
    rospy.spin()


if __name__ == '__main__':
    try:
        __init__()
        
    except rospy.ROSInterruptException:
        pass