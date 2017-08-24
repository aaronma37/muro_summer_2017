To install camera, 

add packages aruco, aruco_localization-master and usb_cam to your catkin_ws/src folder

go to aruco_localization-master/src and open ram_localization.cpp

edit the " CParam.readFromXMLFile("/home/alec/catkin_ws/src/aruco_localization-master/camera_old.yml");" and make it match your catkin_ws (changethe user adn catkin_ws name if different)

camera_old.yml is the calibration file


