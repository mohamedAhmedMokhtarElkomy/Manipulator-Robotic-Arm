# from pyPS4Controller.controller import Controller
# from serial import *
# import time
#
#
# class MyController(Controller):
#
#     def __init__(self, **kwargs):
#         Controller.__init__(self, **kwargs)
#
#
# controller = MyController(interface="/dev/input/js0", connecting_using_ds4drv=False)
#
# serialcomm = Serial('/dev/ttyACM0', 9600)
#
# # serialcomm = serial.Serial('/dev/ttyACM0')
# serialcomm.timeout = 1
#
# def on_x_press(self):
#     serialcomm.write(1)
#     print("sent")
# controller.listen()
#


import subprocess

subprocess.run(['pip','install','--upgrade', 'pip'])

subprocess.run(['pip','install','pyserial'])


import serial
from pyPS4Controller.controller import Controller

send = False
def sending(char):
    send = True
    while send:
        serialcomm.write(bytearray(char, 'ascii'))
        print("L3_up")

def stopSending():
    send = False
    print("=======================================================")

class MyController(Controller):

    def __init__(self, **kwargs):
        Controller.__init__(self, **kwargs)

    def on_R1_press(self):
        serialcomm.write(bytearray('u', 'ascii'))
        print("press R1")
    def on_R1_release(self):
        serialcomm.write(bytearray('0', 'ascii'))
        print("release R1")
    def on_R2_press(self, value):
        serialcomm.write(bytearray('d', 'ascii'))
        print("press R2")
    def on_R2_release(self):
        serialcomm.write(bytearray('0', 'ascii'))
        print("release R2")
    def on_L1_press(self):
        serialcomm.write(bytearray('f', 'ascii'))
        print("press L1")
    def on_L1_release(self):
        serialcomm.write(bytearray('0', 'ascii'))
        print("release L1")
    def on_L2_press(self, value):
        serialcomm.write(bytearray('b', 'ascii'))
        print("press L2")
    def on_L2_release(self):
        serialcomm.write(bytearray('0', 'ascii'))
        print("release L2")
    def on_right_arrow_press(self):
        serialcomm.write(bytearray('r', 'ascii'))
        print("press right arrow")
    def on_left_arrow_press(self):
        serialcomm.write(bytearray('l', 'ascii'))
        print("press left arrow")
    def on_left_right_arrow_release(self):
        serialcomm.write(bytearray('0', 'ascii'))
        print("release arrows")

    def on_x_press(self):
        serialcomm.write(bytearray('x','ascii'))

    def on_square_press(self):
        serialcomm.write(bytearray('s','ascii'))


controller = MyController(interface="/dev/input/js0", connecting_using_ds4drv=False)

serialcomm = serial.Serial("/dev/ttyACM0", 9600)
serialcomm.close()
serialcomm.open()
serialcomm.timeout = 1

controller.listen()

