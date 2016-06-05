# -*- coding: utf-8 -*-
import threading as th
import time



def do1():
    print "1 wake up ", time.ctime(), "/n"
    time.sleep(10)
    print "hello ", time.ctime(), "/n"

def do2():
    print "2 wake up ", time.ctime(), "/n"
    time.sleep(20)
    print "hi ", time.ctime(), "/n"






thread1 = th.Thread(target=do1)
thread2 = th.Thread(target=do2)
thread1.start()
thread2.start()

thread1.join()
thread2.join()




