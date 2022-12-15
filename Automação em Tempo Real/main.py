import numpy as np
import matplotlib.pyplot as plt
import threading
import time
from motor import Motor
from pid import PID
from Constant import *
from interface import Interface
from logger import Logger
from socket import *
import os

#Global variables
#Interface thread object
interfaceThread = Interface()
sem = threading.Semaphore(1)

def readMessage(msg, con):

    if(msg == "exit"):
        print("Exiting...")
        #Shutdown socket
        con.close()
        #kills all threads
        os._exit(1)


    splitMsg = msg.split("/x/")
    motorId = list(map(int, splitMsg[0].split()))
    #pushback motor ids to interface
    for i in motorId:
        interfaceThread.onList.append(i)
    voltage = splitMsg[1]
    #Changes the reference
    sem.acquire()
    interfaceThread.ref_rpm = float(voltage)
    interfaceThread.inputReceived = True
    interfaceThread.controlReference = interfaceThread.ref_rpm
    sem.release()

def startServer():
    host = gethostname()
    port = 51511

    print(f'HOST: {host} , PORT {port}, type "exit" to exit')
    serv = socket(AF_INET, SOCK_STREAM)
    serv.bind((host, port))
    serv.listen(5)
    while 1:
        con, adr = serv.accept()
        while 1:
            msg = con.recv(1024)
            msg = msg.decode()
            readMessage(msg,con)

#step function
def heaviside(t,stepTime,stepVal):
    if t < stepTime:
        return 0
    else:
        return stepVal

# reference input function
def input_function(t):
    #rpm = np.sin(1e-2*t**2 + 1e-3*t + 1)
    rpm = heaviside(t,2,215)
    return rpm


if __name__ == '__main__':
    timeSpan = [0]  # timeSpan
    speed_rpm = []  # reference speed
    errors = [[0]]  # keep track of errors
    dt = 0.001  # sampling rate
    #Master list containing all motors
    motorPool = []

    #Creates a server thread
    serverThread = threading.Thread(target=startServer)
    serverThread.start()
    
    if interfaceThread.inputReceived == False:
        interfaceThread.start()
        

    for i in range(MAX_MOTORS):
        motorPool.append(Motor(i))
        #errors.append([0])


    for m in motorPool:
        m.start()


    loggerThread = Logger(motorPool)
    loggerThread.start()
    
    while (interfaceThread.inputReceived == False):
        pass
    
    for t in np.arange(dt, 10, dt):
        timeSpan.append(t)

        speed_rpm.append(interfaceThread.ref_rpm)
        #Turns on motors in onlist
        for i in interfaceThread.onList:
            motorPool[i].calculateError(interfaceThread.ref_rpm)


    time.sleep(9)
    #sets the reference speed for the interface to half of the reference speed
    sem.acquire()
    interfaceThread.controlReference = interfaceThread.ref_rpm
    sem.release()

    startTime = time.time()
    print("Controlling motors!")
    while (time.time() - startTime < 60):
        sem.acquire()                
        interfaceThread.ref_rpm = interfaceThread.controlReference/2
        sem.release()
        timeSpan.append(timeSpan[-1]+dt)
        speed_rpm.append(interfaceThread.ref_rpm)
        for i in interfaceThread.onList:
            motorPool[i].calculateError(interfaceThread.ref_rpm)

    for motor in motorPool:
        print(f"Motor {motor.id} speed: {motor.Wm}")

    #shutdowns all motors
    os._exit(1)
    