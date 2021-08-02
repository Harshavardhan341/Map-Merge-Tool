#!/usr/bin/env python
import os
import sys
import time
import psutil

#define a function to print cpu percetage every 1 minute
def memory_tracker():
    i = 0
    j=1
    file = open("memory_tracker.txt","w")

    while True:
        memory_info = psutil.virtual_memory()
        print "Memory usage: %5s%%" % memory_info.percent
        #system command to run ros map saver node
       
        if i%60 == 0:
            os.system('mkdir ~/Map-Merge-Tool/maps/map'+str(j))
            map_file = '~/Map-Merge-Tool/maps/map'+str(j)+'/map'+str(j)
            os.system('rosrun map_server map_saver -f '+map_file)
            #write memory percentage and map name to file
            file.write(str(memory_info.percent)+'\t'+map_file+'\n')
            print("saving map"+map_file)
            j+=1

        #kill all ros processes if memory usage is above 95% and break
        if memory_info.percent >= 95:
            os.system('mkdir ~/Map-Merge-Tool/maps/map'+str(j))
            map_file = '~/Map-Merge-Tool/maps/map'+str(j)+'/map'+str(j)
            os.system('rosrun map_server map_saver -f '+map_file)
            os.system('rosnode kill -a')
            break
        i+=1

        time.sleep(1)

#main function
if __name__ == '__main__':
    memory_tracker()
    

