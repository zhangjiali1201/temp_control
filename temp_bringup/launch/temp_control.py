#!/usr/bin/env python
# coding:utf-8

# Copyright: 2016-2020 wwww.corvin.cn ROS小课堂
# Description: 通过键盘遥控小车行进、抓取。
# History:
#   20200317 增加小车抓取功能
#   20200408 增加小车可通过“7”“8”数字键控制夹爪张开闭合角度
#   20200410 修改小车可通过“1”“2”数字键控制夹爪上下移动，“4”“5”张开闭合一定角度

import roslib
import rospy
from geometry_msgs.msg import Twist
import sys, select, termios, tty
from ros_arduino_msgs.srv import AnalogSensorRead
from ros_arduino_msgs.msg import Analog
import time

#调用service: /arduino/test/read读取A0口数值
def client_srv():
    try:
        rospy.wait_for_service("/arduino/test/read")
        print "The service is ready!"
        #rospy.loginfo("The service is ready!")
    except rospy.ServiceException, e:
        rospy.logwarn("Service call failed: %s"%e)

class TEMP():
    def __init__(self):
        rospy.init_node('temp_control_node', anonymous=False)
        rospy.Subscriber('/arduino/sensor/test', Analog, self.callback)
    def callback(self, msg):
        print "The sensor's value is: ", msg.value
        if(msg.value<500):
            print 'heat up'
        elif (msg.value==500):
            print 'keep'
        else:
            print 'cool down'
            #pass

if __name__=="__main__":
    try:
        client_srv()
        TEMP()
        rospy.spin()
    except:
        rospy.loginfo("Node terminated.")
