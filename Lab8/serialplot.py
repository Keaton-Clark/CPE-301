#!/usr/bin/env python
import serial
import time
import os
import threading
import queue
import numpy as np
import matplotlib
import matplotlib.pyplot as plt
import matplotlib.animation as animation
from matplotlib import style
from matplotlib.ticker import (MultipleLocator, FormatStrFormatter,
                               AutoMinorLocator)
import datetime

matplotlib.rc('xtick', labelsize=8)     
matplotlib.rc('ytick', labelsize=10)

global ser, data
data = []
if os.path.exists('/dev/ttyACM0') == True:
    ser = serial.Serial(port='/dev/ttyACM0',baudrate = 9600,parity=serial.PARITY_NONE,
    stopbits=serial.STOPBITS_ONE,bytesize=serial.EIGHTBITS,timeout=1)
else:
    exit()

   
def thread_read():
   max_count = 2000
   while True:
       #read data from arduino
       Ard_data = ser.readline()
       try:
           data.append((5000*int(Ard_data))/1023)
       except ValueError:
           pass
       if len(data) == max_count:
           data.pop(0)
   
def thread_plot():
       global fig,animate, ax1, ax2
       fig = plt.figure()
       ax1 = fig.add_subplot(2,1,1)
       ax2 = fig.add_subplot(2,1,2)
       ani = animation.FuncAnimation(fig, animate, interval=0)
       plt.show()
   
def animate(i):
    global ax1, ax2
    data2 = data[-100:]
    ax2.clear()
    ax2.plot(range(0, len(data2)), data2)
    ax1.clear()
    ax1.set_ylim([0,5115])
    ax1.set_xlim([0,2000])
    ax1.plot(range(0, len(data)), data)

read_thread = threading.Thread(target=thread_read)
read_thread.start()

plot_thread = threading.Thread(target=thread_plot)
plot_thread.start()

