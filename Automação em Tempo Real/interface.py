import threading
import time
from Constant import *

class Interface(threading.Thread):
    def __init__(self):
        threading.Thread.__init__(self)
        self.ref_rpm = 0
        self.controlReference = 0
        self.onList = []
        self.inputReceived = False

    def run(self):
        while(True):
        #receive input and convert to int list
            msg = input("Enter the motors you want to turn on: ")
            #separates the string into a list of ints
            motorId = [int(i) for i in msg.split()]

            if(self.verifyList(motorId)):
                for i in motorId:
                    self.onList.append(i)
                break
        self.ref_rpm = float(input("Enter reference in RPM: "))
        print(f"Turning on motors {self.onList}!!!")
        self.inputReceived = True


    def verifyList(self,motorId):
        #verifies if the list is empty
        if(len(motorId) == 0):
            return False
        #verify all numbers are less than MAX_MOTORS
        for i in motorId:
            if(i > MAX_MOTORS-1):
                print("Invalid motor ID, try again")
                return False

        #verify if the list is less than 12
        if(len(motorId) > 12):
            print("Too many motors, try again")
            return False

        #Verify if the list has sequencial numbers
        for i in motorId:
            if(i+1  in motorId or i-1 in motorId):
                print("Invalid list, try again")
                return False

        return True