from pyPS4Controller.controller import Controller
from threading import Thread, Event
import RPi.GPIO as GPIO
import time

usleep = lambda x: time.sleep(x/1000000.0)
usleep(100)

#SERVO
#GPIO.setmode(GPIO.BOARD)
#GPIO.setup(11,GPIO.OUT)
#pwm=GPIO.PWM(11, 50)

#ELBOW STEPPER MOTOR
GPIO.setmode(GPIO.BOARD)
GPIO.setup(10,GPIO.OUT)
GPIO.setmode(GPIO.BOARD)
GPIO.setup(12,GPIO.OUT)



elbowEvent = Event()
shoulderEvent = Event()

def setAngle(angle):
    duty = angle / 18 + 3
    GPIO.output(11, True)
    pwm.ChangeDutyCycle(duty)
    time.sleep(1)
    GPIO.output(11, False)
    pwm.ChangeDutyCycle(duty)


def rotate(event, pin_step):
    print("thread is running")
    while(1):
        if event.is_set():        
            GPIO.output(pin_step, True)
            
        usleep(10000)
        GPIO.output(pin_step, False)
        usleep(10000)

#pwm.start(0)
#setAngle(80)

class MyController(Controller):

    def __init__(self, **kwargs):
        Controller.__init__(self, **kwargs)

    def on_R1_press(self):
        GPIO.output(12, True)
        shoulderEvent.set()
        print("on_R1_press")
        
    def on_R1_release(self):
        shoulderEvent.clear()
        print("on_R1_release")
        
    def on_R2_press(self, value):
        GPIO.output(12, False)
        shoulderEvent.set()
        
    def on_R2_release(self):
        shoulderEvent.clear()
        
    def on_L1_press(self):

        print("press L1")
    def on_L1_release(self):

        print("release L1")
    def on_L2_press(self, value):

        print("press L2")
    def on_L2_release(self):

        print("release L2")
    def on_right_arrow_press(self):

        print("press right arrow")
    def on_left_arrow_press(self):

        print("press left arrow")
    def on_left_right_arrow_release(self):

        print("release arrows")

    def on_x_press(self):
        setAngle(140)
        print("x")

    def on_square_press(self):
        setAngle(80)
        print("y")

t1 = Thread(target=rotate, args=(shoulderEvent, 10))
#t2 = Thread(target=shoulder, args=(shoulderEvent, 1))
t1.start()
#t2.start()

controller = MyController(interface="/dev/input/js0", connecting_using_ds4drv=False)
controller.listen()

#rotate(10)