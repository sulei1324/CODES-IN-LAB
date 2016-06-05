import threading
import os

def a(arg):
    print arg, os.getpid()
    

threads = []
print os.getpid()
for i in xrange(4):
    t = threading.Thread(target=a, args=(i, ))
    threads.append(t)

for i in xrange(4):
    threads[i].start()

for i in xrange(4):
    threads[i].join()


