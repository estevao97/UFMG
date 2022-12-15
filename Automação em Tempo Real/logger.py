import threading
import time

class Logger(threading.Thread):
    def __init__(self, motorPool):
        threading.Thread.__init__(self)
        self.motorPool = motorPool
    
    def run(self):
        file1 = open("log.txt", "a")
        start = time.time()
        while(True):
            file1.write(f"Time: {round(time.time() - start,1)} seconds \n")
            for i in range(len(self.motorPool)):
                file1.write(f"Motor {self.motorPool[i].id} speed: {self.motorPool[i].Wm} \n")
            file1.write("\n ################# \n\n")
            time.sleep(1)
