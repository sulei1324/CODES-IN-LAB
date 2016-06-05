import cv2 as cv
import numpy as np
import os
import math



src = r'G:\sulei\workplace\atlas\dst\dst'
dst = r'G:\sulei\workplace\atlas\dst\maxed'
images_file = os.listdir(src)
max_w = 11072
max_h = 8528


for image_name in images_file:
    out_image = np.zeros((max_h, max_w), dtype=np.uint16)
    a_image = cv.imread(src + '\\' + image_name, cv.CV_LOAD_IMAGE_UNCHANGED)
    a_image_shape = a_image.shape
    print image_name, a_image_shape
    a_image_width = a_image_shape[1]
    a_image_height = a_image_shape[0]
    if (a_image_width / 2) * 2 != a_image_width:
        t_image_width = a_image_width + 1
    else:
        t_image_width = a_image_width
    if (a_image_height / 2) * 2 != a_image_height:
        t_image_height = a_image_height + 1
    else:
        t_image_height = a_image_height
    tmp_image = np.zeros((t_image_height, t_image_width), dtype=np.uint16)
    tmp_image[0: a_image_height, 0: a_image_width] = a_image   
    out_image[max_h / 2 - t_image_height / 2 : max_h / 2 + t_image_height / 2,\
                     max_w / 2 - t_image_width / 2 : max_w / 2 + t_image_width / 2] = tmp_image
    cv.imwrite(filename=dst+'\\maxed_'+image_name, img=out_image)
    
    
    





# 8528 11072