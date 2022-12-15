import threading
import numpy as np
import matplotlib.pyplot as plt
import time
from pid import PID
from Constant import *

'''PID Parameters'''
Kp = 10
Ki = 16
Kd = 2
onList = [0]*30
semMotor = threading.Semaphore(3)

class Motor(threading.Thread):
    def __init__(self,id):
        threading.Thread.__init__(self)
        self.id = id
        
        self.R = 1		        #armature_resistance
        self.L = 0.5		    #armature_inductance	    
        self.J = 0.01		    #inertia
        self.B = 0.3		    # viscous_friction
        self.Kb = 0.01		    #eletric_constant
        self.Wm = 0			    #Speed
        self.Kt = 0.01
        self.dt = 0.001         #Sampling time
        self.state = False      #Flag for state of motor
        self.outputs = [0, 0]
        self.errors = [0]         #error for controlling
        self.pid = PID(Kp, Ki, Kd, self.dt)

    # updates the output with the pid output
    def update(self, v):
        output_now = (v + (self.L * self.B * self.outputs[-1] / self.dt / self.Kt)
         + (self.L * self.J * (2 * self.outputs[-1] - self.outputs[-2]) /
          self.Kt / (self.dt ** 2))+(self.R * self.J * self.outputs[-1] /
           self.Kt)) / ((self.L * self.B / self.dt / self.Kt) + 
           (self.L * self.J / self.Kt / (self.dt**2))+
           (self.R * (self.B + self.J) / self.Kt) - self.Kb)
        self.outputs.append(output_now)
        self.Wm = self.outputs[-1]

    def get_outputs(self):
        return self.outputs[2:]
    
    def plotSpeed(self,time,speed_rpm):
        plt.plot(time, speed_rpm, label="Reference",
            color='blue')
        plt.plot(time, self.get_outputs(), label="Output", color='red')
        plt.xlabel('Time(s)')
        plt.ylabel('Velocidade (rpm)')
        plt.legend()
        plt.grid()
        plt.show()  

    def calculateError(self,ref_rpm):
        error_now = ref_rpm - self.outputs[-1]  # calculating the error
        self.errors.append(error_now)

        integral, derivative, proportional = self.pid.calculate(self.errors)
        v = integral + derivative + proportional
        self.update(v)

    def run(self):
        time.sleep(1)
    
    def turnOn(self):
        self.state = True
