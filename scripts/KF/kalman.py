#! /usr/bin/python

import matplotlib.pyplot as plt 
import numpy as np
from scipy import linalg
import math
from math import pow,atan2,sqrt,cos,sin,asin,pi
import rosbag
import rospy
from std_msgs.msg import UInt8, String
from geometry_msgs.msg import Twist, Vector3
from ros_myo.msg import MyoArm
from ros_myo.msg import EmgArray
from sensor_msgs.msg import Imu
import time
import tf


#------------ Getting data from file ------------

count=0
accelerometer=[0,0,0]
gyroscope=[0,0,0]
magnetometer=[0,0,0,0]


# load the bag file

#bag = rosbag.Bag('Stationary_Arm_30_2017-07-17-16-38-14.bag')
bag = rosbag.Bag('Stationary_30_2017-07-17-16-17-58.bag')

# storages the data from bag file to accelerometer, gyro and magnetometer into matrices

for topic, msg, t in bag.read_messages(topics=['/myo_imu']):
      count=count + 1
      accelerometer = np.vstack([accelerometer,[msg.linear_acceleration.x,msg.linear_acceleration.y,msg.linear_acceleration.z]])
      gyroscope     = np.vstack([gyroscope,[msg.angular_velocity.x,msg.angular_velocity.y,msg.angular_velocity.z]])
      magnetometer  = np.vstack([magnetometer,[msg.orientation.x,msg.orientation.y,msg.orientation.z,msg.orientation.w]])

#init vectors

length = len(magnetometer)
angArr = np.zeros(shape=(length,3))               #Vector to storage new angular orientations
T = np.zeros(shape=(length,1))                    #time vector

# Transforming quaternions to euler angles and generate the vector of samples

for i in range(0,length):
      angArr[i] = tf.transformations.euler_from_quaternion(magnetometer[i]) 
      T[i] = i

#convert from radians to degrees
#angArr = 180/pi*np.array(angArr)

#Separate the data into vectors of measurments
m_omega_x = gyroscope[:,0]
m_omega_y = gyroscope[:,1]
m_omega_z = gyroscope[:,2]
m_theta_x = angArr[:,0]
m_theta_y = angArr[:,1]
m_theta_z = angArr[:,2]

# z vector of measurments wil be defined later


#------------ End of getting data ---------------







#------------ Linear System definition ------------

# linear system definition
#Sample time
dt = 1
# radius constant
r = 0.3

#create the vectors with zeros or ones

pos_z = np.zeros(shape=(length,1))          #linear pos in z axis
pos_y = np.zeros(shape=(length,1))          #linear pos in y axis
vel_z = np.zeros(shape=(length,1))          #linear vel in z axis
vel_y = np.zeros(shape=(length,1))          #linear vel in y axis

m_pos_z = np.zeros(shape=(length,1))        #angular pos in z axis
m_pos_y = np.zeros(shape=(length,1))        #angular pos in y axis
m_vel_z = np.zeros(shape=(length,1))        #angular vel in z axis
m_vel_y = np.zeros(shape=(length,1))        #angular vel in y axis

a_z = np.zeros(shape =(length,1))           #acceleration in z axis
a_y = np.zeros(shape =(length,1))           #acceleration in y axis

#increment the T vector in 1
#for i in range(0,length):
        #  a_z[i] = cos(i)
        #  a_y[i] = sin(i)




# lin sitem Type  is   x' = Ax + Bu
# and its output is    y = Cx
# so for a 4 state system we have the following:

# #State transition matrix
A = [[1,0,dt,0],
      [0,1,0,dt],
      [0,0,1,0],
      [0,0,0,1]]

#control matrix
B = [[math.pow(dt,2)/2,0],
      [0,math.pow(dt,2)/2],
      [dt,0],
      [0,dt]]

# C matrix 
# C = [[1/r,0,0,0],
#       [0,1/r,0,0],
#       [0,0,1/r,0],
#       [0,0,0,1/r]]    

C = [[1,0,0,0],
      [0,1,0,0],
      [0,0,1,0],
      [0,0,0,1]]    

#output vector
y = [[0],
      [0],
      [0],
      [0]]


#------------End of system definition ------------


#-------------Kalman definitions -----------------

# covariance matrices
#Process covariance
# R1 = 0.000005 
# R2 = 0.000003
# R3 = 0.022
# R4 = 0.020

R1 = 0.01
R2 = 0.01
R3 = 0.01
R4 = 0.01


R = [[R1,0,0,0],
     [0,R2,0,0],
     [0,0,R3,0],
     [0,0,0,R4]]

#Measurment covariance
# Q1 = 0.00000403921 
# Q2 = 0.00000278561
# Q3 = 0.021578
# Q4 = 0.016467

Q1 = 0.2
Q2 = 0.2
Q3 = 0.2
Q4 = 0.2

Q = [[Q1,0,0,0],
     [0,Q2,0,0],
     [0,0,Q3,0],
     [0,0,0,Q4]]

# kalman gains definition

k_1 = 0.0
k_2 = 0.0
k_3 = 0.0
k_4 = 0.0

K = [[k_1,0,0,0],
     [0,k_2,0,0],
     [0,0,k_3,0],
     [0,0,0,k_4]]

#variables definition

#-previous state

mt_1 = 0.0
mt_2 = 0.0
mt_3 = 0.0
mt_4 = 0.0

mt_ = [[mt_1],
       [mt_2],
       [mt_3],
       [mt_4]]

#predicted state

pmt_1 = 0.0
pmt_2 = 0.0
pmt_3 = 0.0
pmt_4 = 0.0

pmt_ = [[pmt_1],
        [pmt_2],
        [pmt_3],
        [pmt_4]]

#corrected state

mt1 = 0.0
mt2 = 0.0
mt3 = 0.0
mt4 = 0.0

mt = [[mt1],
      [mt2],
      [mt3],
      [mt4]]
#previous covariance

St_1 = 0.0
St_2 = 0.0
St_3 = 0.0
St_4 = 0.0

St_ = [[St_1,0,0,0],
       [0,St_2,0,0],
       [0,0,St_3,0],
       [0,0,0,St_4]]

#predicted covariance

pSt_1 = 0.0
pSt_2 = 0.0
pSt_3 = 0.0
pSt_4 = 0.0

pSt_ = [[pSt_1,0,0,0],
        [0,pSt_2,0,0],
        [0,0,pSt_3,0],
        [0,0,0,pSt_4]]

#corrected covariance

St1 = 0.0
St2 = 0.0
St3 = 0.0
St4 = 0.0

St = [[St1,0,0,0],
       [0,St2,0,0],
       [0,0,St3,0],
       [0,0,0,St4]]
# ---------------End of definitions ---------------

#----------------kalman filter function-------------

#def KF (mt_, St_, ut, zt):



for t in range(0,length):
     
      #simulated control input
      ut = [a_y[t], 
            a_z[t]]
      #measurment vector
      zt = [[m_theta_z[t]],
            [m_theta_y[t]],
            [m_omega_z[t]],
            [m_omega_y[t]]]

      # Step 1: Predictive

      #predict the state Ax+Bu = x' 
      pmt_ = np.add( np.dot( A , mt_ ) , np.dot( B , ut ) )
      #predict the covariance matrix
      pSt_ = np.add( np.dot( np.dot( A , St_ ) , np.transpose(A) ) , R )

      # Step 2: Belief compute and corrective

      #determinate the Kalman gain
      K = np.dot( np.dot( pSt_ , np.transpose(C)) , linalg.inv( np.add( np.dot( np.dot( C , pSt_ ) , np.transpose(C) ) , Q)))
      #determinate the corrected state
      mt = np.add( pmt_ , np.dot( K , np.subtract( zt , np.dot( C , pmt_ ) ) ) )
      #determinate the corrected covariance matrix
      St = np.dot( np.subtract( np.identity(4) , np.dot( K , C ) ) , pSt_ )
    
      # convert measurment to state output vector
      y = np.dot(C,zt)

      # new values now becomes last 
      mt_ = mt
      St_ = St

      # separate state vector into individual arrays

      #KF results
      pos_z[t] = mt[0]
      pos_y[t] = mt[1]
      vel_z[t] = mt[2]
      vel_y[t] = mt[3]

      #measurments
      m_pos_z[t] = y[0]
      m_pos_y[t] = y[1]
      m_vel_z[t] = y[2]
      m_vel_y[t] = y[3]



#plot the result

plt.figure(1)
plt.title('KF result (b) vs zt (gr)')
plt.plot(T,vel_z)
plt.hold('on')
plt.plot(T,m_vel_z)
plt.grid('on')
plt.ylabel('m')
plt.xlabel('No. Samples')

plt.show()

    #Return the values
#    return [mt, St]
    
#if __name__ == '__main__':

#define zt and multiply by -1 
# u = A-BKC is the control input and its reference is 0