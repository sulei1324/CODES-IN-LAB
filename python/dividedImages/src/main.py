import tifffile as tf
import numpy as np
import os
import shutil
import time

src = 'G:\\sulei\\workplace\\fmostd\\src\\'
dst = 'G:\\sulei\\workplace\\fmostd\\src\\test\\mostd\\'
tmp = 'G:\\sulei\\workplace\\fmostd\\src\\test\\tmp\\'
# if not os.path.exists(dst):
#     os.mkdir(dst)
if not os.path.exists(tmp):
    os.mkdir(tmp)
width = 10000
height = 14000
pre = ''
post = '.tif'
zRange = (1, 5)
level = zRange[1] - zRange[0] + 1
stack_width = 512
stack_height = 512
stack_level = 50
x_section_num = width / stack_width + 1 if ((width % stack_width) != 0) else (width / stack_width)
y_section_num = height / stack_height + 1 if ((height % stack_height) != 0) else (height / stack_height)
z_section_num = level / stack_level + 1 if ((level % stack_level) != 0) else (level / stack_level)
print x_section_num, y_section_num, z_section_num
thread_num = 1
work_pool = []
whole_work_in_a_image = x_section_num * y_section_num
each_thread_job_num = (whole_work_in_a_image / thread_num) if (whole_work_in_a_image % thread_num == 0) else ((whole_work_in_a_image / thread_num) + 1)
# print each_thread_job_num, whole_work_in_a_image
thread_serial = 0
job_serial = 0
for i in xrange(x_section_num):
    for j in xrange(y_section_num):
#         print (i, j),  job_serial, thread_serial
        if job_serial == 0:
            work_pool.append([])
        if job_serial == each_thread_job_num:
            job_serial = 0
            thread_serial += 1
            work_pool.append([])
        work_pool[thread_serial].append((i, j))
        job_serial += 1

print work_pool

z_serail = 0
worked_num = 0     
for i in xrange(zRange[0], zRange[1] + 1):
    if worked_num == 0:
#         if not os.path.exists(dst + 'z' + '%d'%(z_serail)):
#             os.mkdir(dst + 'z' + '%d'%(z_serail))
        if not os.path.exists(tmp + 'z' + '%d'%(z_serail)):
            os.mkdir(tmp + 'z' + '%d'%(z_serail))
#         print dst + 'z' + '%d'%(z_serail), tmp + 'z' + '%d'%(z_serail)
        for i1 in xrange(y_section_num):
#             if not os.path.exists(dst + 'z' + '%d'%(z_serail) + '\\y' + '%d'%(i1)):
#                 os.mkdir(dst + 'z' + '%d'%(z_serail) + '\\y' + '%d'%(i1))
            if not os.path.exists(tmp + 'z' + '%d'%(z_serail) + '\\y' + '%d'%(i1)):
                os.mkdir(tmp + 'z' + '%d'%(z_serail) + '\\y' + '%d'%(i1))
#             print dst + 'z' + '%d'%(z_serail) + '/y' + '%d'%(i1), tmp + 'z' + '%d'%(z_serail) + '/y' + '%d'%(i1)
    read_image_name = pre + '%05d'%(i) +post
#     print read_image_name
    print time.ctime()
    this_image = tf.imread(src + read_image_name)
    for j in work_pool:
        this_thread_work_num = len(j)
        for k in xrange(this_thread_work_num):
            this_work = j[k]
            x_serial = this_work[0]
            y_serial = this_work[1]
            work_file_name = 'z' + '%d'%(z_serail) + '\\y' + '%d'%(y_serial) + '\\' + '%d'%(x_serial) + '_'  + '%d'%(y_serial) + '_' + '%d'%(z_serail) + '.tif'
            tmp_save_file_name = tmp + 'z' + '%d'%(z_serail) + '\\y' + '%d'%(y_serial) + '\\' + '%d'%(x_serial) + '_'  + '%d'%(y_serial) + '_' + '%d'%(z_serail) + '.tif'
#             print work_file_name, tmp_save_file_name

            just_4_tmp_image = np.zeros((stack_height, stack_width), np.uint16)
            x_roi = [x_serial * stack_width, (x_serial + 1) * stack_width]
            y_roi = [y_serial * stack_height, (y_serial + 1) * stack_height]
            if x_roi[1] > width:
                x_roi[1] = width
            if y_roi[1] > height:
                y_roi[1] = height
#             print x_roi, y_roi, tmp_image.shape
#             print x_roi, y_roi
            just_4_tmp_image[0 : y_roi[1] - y_roi[0],  0 : x_roi[1] - x_roi[0]] = this_image[y_roi[0] : y_roi[1], x_roi[0]: x_roi[1]]
            just_4_tmp_image = just_4_tmp_image.reshape((1, just_4_tmp_image.shape[0], just_4_tmp_image.shape[1]))
            if worked_num ==0:
                tmp_image = just_4_tmp_image
            else:
                tmp_image = tf.imread(tmp + work_file_name)
                if worked_num == 1:
                    tmp_image = tmp_image.reshape((1, tmp_image.shape[0], tmp_image.shape[1]))
#                 print tmp_image.shape, just_4_tmp_image.shape
                tmp_image = np.concatenate((tmp_image, just_4_tmp_image))
#             print tmp_image.shape
            tf.imsave(tmp_save_file_name, tmp_image)
    if worked_num == stack_level - 1 or i == zRange[1] :
        shutil.copytree(tmp + 'z' + '%d'%(z_serail), dst + 'z' + '%d'%(z_serail))
        shutil.rmtree(tmp + 'z' + '%d'%(z_serail))
#         print tmp + 'z' + '%d'%(z_serail), '-->', dst + '%d'%(z_serail)
        z_serail += 1
        worked_num = 0
    else:
        worked_num += 1
    print time.ctime()

    
            

