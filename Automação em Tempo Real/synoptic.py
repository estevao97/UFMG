from socket import *
from Constant import *

def verifyList(motorId):
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

host = gethostname()
port = 51511
cli = socket(AF_INET, SOCK_STREAM)
cli.connect((host, port))
while 1:
    msg = input("Enter the motors you want to turn on: ")
    #Verifies if the message is exit
    if msg == "exit":
        cli.send(msg.encode())
    motorId = [int(i) for i in msg.split()]
    if(verifyList(motorId)):
        msg = msg + " /x/ " + input("Enter reference in RPM: ")
        cli.send(msg.encode())
