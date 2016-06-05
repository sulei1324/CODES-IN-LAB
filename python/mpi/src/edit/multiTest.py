import multiprocessing as mp
import os

def worker(num,input_queue):
    print 'worker:',num
    for inp in iter(input_queue.get,'stop'):
        print 'executing %s' % inp
        os.popen('./mmul.x < ' +inp+ ' >' +inp+ '.out')
    return

if __name__=='__main__':
    input_queue=mp.Queue()
    for i in range(4):
        input_queue.put('in'+str(i))
    
    for i in range(4):
        input_queue.put('stop')
    
    for i in range(4):
        p=mp.Process(target=worker,args=(i,input_queue))
        p.start()
