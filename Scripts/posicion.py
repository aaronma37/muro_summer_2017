
import rospy
from muro_summer_2017.msg import Controller
from muro_summer_2017.msg import def_pos_X

class controller():

    def __init__(self):
        #create the Robot node
        rospy.init_node('control_sys',anonymous=True)
        #create the publisher, topic name and object
   self.control_pub = rospy.Publisher('ctrl_topic', Control, queue_size=10)
        
