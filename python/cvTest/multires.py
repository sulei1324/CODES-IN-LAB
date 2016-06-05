import cv2 as cv
import multiprocessing as mp
import os, time, random

def single_fun(image_name, image_src, image_dst):
    try:
        print image_name, os.getpid()
        image_in = cv.imread(image_src + "\\" +image_name, cv.CV_LOAD_IMAGE_UNCHANGED)
        in_shape = image_in.shape
        print in_shape
        width = in_shape[1]
        height = in_shape[0]
        new_w = int(round(width * 0.04))
        new_h =  int(round(height * 0.04))
        out_shape = (new_w, new_h)
        print out_shape
        image_out = cv.resize(image_in, out_shape)
        print image_out.shape
        cv.imwrite(image_dst + "\\" + "25_" + image_name, image_out)
    except Exception, e:
        print "Error: ", image_name, e
        
        
     
 
if __name__ == "__main__":
    res_pool = mp.Pool(processes=6)
    src = r"Z:\AppData\TDI\part1\TDI072\resample-1x1x1"
    dst = r"W:\lsu\registration\TDI072\resam"
    files = os.listdir(src)
    for a_file in files:
        res_pool.apply(func=single_fun, args=(a_file, src, dst))
    res_pool.close()
    res_pool.join()
    print "all done!"

# def long_time_task(name):
#     print 'Run task %s (%s)...' % (name, os.getpid())
#     start = time.time()
#     time.sleep(random.random() * 3)
#     end = time.time()
#     print 'Task %s runs %0.2f seconds.' % (name, (end - start))
# 
# if __name__=='__main__':
#     print 'Parent process %s.' % os.getpid()
#     p = mp.Pool()
#     for i in range(5):
#         p.apply_async(long_time_task, args=(i,))
#     print 'Waiting for all subprocesses done...'
#     p.close()
#     p.join()
#     print 'All subprocesses done.'