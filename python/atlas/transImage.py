import cv2 as cv
import os
import numpy as np
import multiprocessing as mpg


def transFunc(ims):
    try:
        print ims
        src = r'G:\sulei\workplace\atlas\dst\pngs' + '\\' + ims
        dst = r'G:\sulei\workplace\atlas\dst\dst'
        color_map = dict()
        sid_name_file = open(r'G:\sulei\workplace\atlas\mapword.txt')
        scount = 1
        for a_line in sid_name_file:
            sep_location = a_line.find('\t')
            sid = a_line[0: sep_location]
            color_map[sid] = scount * 40
            scount += 1
        background_color = 251    
          
        images_names = os.listdir(src)
        i = 1
        for a_image_name in images_names:
            if i == 2:
                break
            in_image = cv.imread(filename=src+'\\'+a_image_name)
            i += 1
        image_shape = in_image.shape
        out_image = np.zeros(image_shape[0: 2], dtype=np.uint16)
        index = 1
        for a_image_name in images_names:
            if index > 1:
                break
            s_id = a_image_name[16: len(a_image_name) - 4]
            s_color = color_map[s_id]
            print s_color
            print "reading: ", a_image_name
            in_image = cv.imread(filename=src+'\\'+a_image_name)
            in_image = cv.cvtColor(in_image, cv.cv.CV_RGB2GRAY)
            print out_image.shape
            print np.where(in_image != background_color)
            out_image[np.where(in_image != background_color)] = s_color
            print out_image.shape
            index += 1   
        out_image_name = dst + '\\' + ims + '.tif'
        print "writing: ", out_image_name
            
#         cv.imwrite(out_image_name, out_image)
    except Exception, e:
        print 'wrong', ims, e

def testFuc(x):
    print x


    
if __name__=='__main__':
    work_pool = mpg.Pool(processes=1)
    src = r'G:\sulei\workplace\atlas\dst\pngs'   
    pngs_files = os.listdir(src)
    index = 1
    for pngs_in_a_file in pngs_files:
        if index > 1:
            break
        image_serial = pngs_in_a_file
        index += 1
        work_pool.apply_async(func=transFunc, args=(image_serial, ))
     
    work_pool.close()
    work_pool.join()

    print "all done!"


