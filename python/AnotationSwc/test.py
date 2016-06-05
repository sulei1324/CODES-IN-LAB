import numpy as np
import cv2 as cv

a = np.zeros((100, 100), dtype=np.uint8)
print a
b =  cv.cvtColor(a, cv.cv.CV_GRAY2RGB)
b[20 : 50, 60 : 80, 1] = 255

print b.shape
cv.imwrite('1.tif', b)