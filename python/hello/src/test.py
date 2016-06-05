import numpy as np
import cv2
import os

# I = cv2.imread('test_02000-02290_40-63_31-1.tif', cv2.CV_LOAD_IMAGE_UNCHANGED)
# I1 = np.uint8((I / np.max(I)) * (2.0 ** 8 - 1))
# I2 = np.uint8((I / 4095) * (2.0 ** 8 - 1))
# print np.max(I), np.min(I)
# scale = 256.0 / (np.max(I) - np.min(I))
# print scale
# I3 = (I - np.min(I)) * scale
# print I3.dtype
# print I.dtype
# I = np.uint8((I - np.min(I)) * scale)
# print I.dtype
# I = cv2.imread('test_02000-02290_40-63_31-1.tif', cv2.CV_LOAD_IMAGE_UNCHANGED)
# print I.dtype

a = 'sss'
b = 'sss'

print a + b, ' sdfsdfsd'


# print os.path.exists('G:/sulei/workplace/montage/test/00002/00002-1-2.tif')
# 
# flag = True
# for i in xrange(10):
#     if i < 5:
#         continue
#     if flag is True:
#         print i - 1
#         flag = False
#     print i




# print I.dtype
# I1 = I / (2 ** 16 - 1.0) * (2 ** 8 - 1)
# print I1.dtype
# I1 = np.uint8(I1)
# print I1.dtype


# I = np.array((0, 255, 256, 500), np.uint16)
# print I.dtype, I, np.uint8(I)
# I1 = (I / (5000.0)) * (2 ** 8 - 1)
# print I1.dtype, I1
# I1 = np.uint8(I1)
# print I1.dtype, I1
# I2 = np.uint8((I / (5000.0)) * (2 ** 8 - 1))
# print I2.dtype, I2
# 
# print np.max(I)



# /usr/mpi/gcc/openmpi-1.4.3/bin/mpirun -n 20 -host cu01 -host cu02 -host cu03 -host cu04 -host cu05 python montageApp.py
