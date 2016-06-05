# -*- coding: utf-8 -*-

import cv2 as cv
import numpy as np
from numpy import dtype

ref_images = []
for i in xrange(10):
    this_name = "./src/ref/%d.tif"%i
    this_ref_image = cv.imread(this_name, cv.CV_LOAD_IMAGE_UNCHANGED)
    ref_images.append(this_ref_image)

record_txt = open("record.txt", 'a')

image1 = cv.imread('5.jpg', cv.CV_LOAD_IMAGE_UNCHANGED)
retval, image1 = cv.threshold(image1, 50, 255, cv.THRESH_BINARY)
image1 = cv.cvtColor(image1, cv.COLOR_BGR2GRAY)
image1 = image1 > 10
image1 = image1.astype(np.uint8)
image1 = image1 * 255
 
flag_in = False
s = 0
block_num = 0
char_num_array = []
for i in xrange(image1.shape[0]):
    if np.all(image1[i, :] == 255):
        if flag_in:
            flag_in = False
            block = image1[s: i, :]
            block_name = "./src/%d.tif"%block_num
            char_num = 0
            s_char = 0
            flag_block = False
            for j in xrange(block.shape[1]):
                if np.all(block[:, j] == 255):
                    if flag_block:
                        flag_block = False
                        char_block = block[:, s_char : j]
                        char_name = "./src/char_%d_%d.tif"%(block_num, char_num)
                        cv.imwrite(char_name, char_block)
                        char_num += 1
                else:
                    if not flag_block:
                        s_char = j
                        flag_block = True            
#             cv.imwrite(block_name, block)
            char_num_array.append(char_num)
            block_num += 1
    else:
        if not flag_in:
            s = i
            flag_in = True
 
for i in xrange(block_num):
    char_num = char_num_array[i]
    this_record = ""
    for j in xrange(char_num):
        char_name = "./src/char_%d_%d.tif"%(i, j)
        this_char_image = cv.imread(char_name, cv.CV_LOAD_IMAGE_UNCHANGED)
        for k in xrange(10):         
            if np.all(this_char_image == ref_images[k]):
                this_record += str(k)
    record_txt.write(this_record + "\t")

record_txt.close()        
#         
# 
# # cv.imshow("image6", image5)
# # cv.imwrite("r.jpg", image6)
# # cv.waitKey()
