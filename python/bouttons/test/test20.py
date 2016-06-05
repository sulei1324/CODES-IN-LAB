import cv2 as cv
import numpy as np

a = np.zeros((4, 4), dtype=np.uint16) 
b = cv.bitwise_not(a)
if b is not None:
    print a
    print b