#!/usr/bin/env python
import rospy
import sys
from geometry_msgs.msg import Twist
from turtlesim.msg import Pose
from math import atan2,sqrt,pi,pow

class turtle_control():

    def __init__(self):
        #crear nodo
        rospy.init_node('turtle_control',anonymous = True)
        #create the publicador con el topico turtuga velocidad
        self.velocities_pub = rospy.Publisher('/turtle1/cmd_vel', Twist, queue_size = 10)
        #posicion de la tortuga
        self.pose_sub = rospy.Subscriber('/turtle1/pose', Pose, self.callback)
        #cerar generalizado y coordinar
        self.A = Pose()
        self.rate = rospy.Rate(10)
        #definirvariables al limite de la tortuga
        self.steering_ang_limit = pi  #giro angular
        self.lin_velocity_limit = 1 #velocidad deseada
        self.d_tolerance = 0.001 # tolerancia por decir default
        #ganiancia de P
        self.Kp_vel = 2 # velocidad lineal
        self.Kp_theta = 5 #angulo 

    #actualiza el vector self.A
    def callback (self,data):
        self.A = data
        self.A.x = round(self.A.x, 3) #obtener pose X
        self.A.y = round(self.A.y, 3) #obtener pose Y
        self.A.theta = round(self.A.theta, 2) #obtener pose Teta

    #control computacional angular 
    def ang_speed_control(self, Apoint):
        angular_vel = self.Kp_theta * (atan2(Apoint.y-self.A.y, Apoint.x-self.A.x)-self.A.theta)
        if angular_vel > self.steering_ang_limit:
            angular_vel = self.steering_ang_limit
        elif angular_vel < (-self.steering_ang_limit):
            angular_vel = -self.steering_ang_limit
        return angular_vel

    #control computacional lineal
    def lin_speed_control(self, Apoint):
        velocity = self.Kp_vel * (sqrt(pow((Apoint.x-self.A.x), 2)+pow((Apoint.y-self.A.y), 2)))
        #inicializa en valor de velocidad
        if velocity > self.lin_velocity_limit:
            velocity = self.lin_velocity_limit
        elif velocity < (-self.lin_velocity_limit):
            velocity = -self.lin_velocity_limit
        #retorno
        return velocity

    #movimiento de la tortuga
    def move_to_coordinate(self):
        Apoint = Pose()
        #consola puntos de desplazamiento
        Apoint.x = input(" x value (size max 10):")
        Apoint.y = input(" y value (size max 10):")
        v_msg = Twist()
        #inicializa las variables en ceros
        v_msg.linear.y = 0
        v_msg.linear.z = 0
        v_msg.angular.x = 0
        v_msg.angular.y = 0
        #ejecuta el control, ussando pitagoras
        while sqrt(pow((Apoint.x-self.A.x), 2)+pow((Apoint.y-self.A.y), 2))>self.d_tolerance:
            #obtiene lineal y angular su velucidad de sus controladores
            v_msg.linear.x = self.lin_speed_control(Apoint)
            v_msg.angular.z = self.ang_speed_control(Apoint)
            #publish velocidad
            self.velocities_pub.publish(v_msg)
            self.rate.sleep()
        #se detiene el robot cuando este alla alcanzo su punto de X and Y
        v_msg.linear.x = 0
        v_msg.angular.z = 0
        self.velocities_pub.publish(v_msg)
        rospy.spin()

#main
if __name__ == '__main__':
    try:
        #crea la tortuga y la ejecucion del programa
        turtle = turtle_control()
        turtle.move_to_coordinate()
    except rospy.ROSInterruptException: pass
