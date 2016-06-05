import cv2 
import cv2.cv as cv
import string
import numpy
from cv2 import CV_LOAD_IMAGE_UNCHANGED


def a(e, x, y, *arg, **karg):
    global image1
    if e == cv2.EVENT_LBUTTONDOWN:
        cv2.circle(image1, (x, y), 5, (0, 0, 255), 2)
        cv2.imshow("test2", image1)


image1 = cv2.imread("1.png", cv2.CV_LOAD_IMAGE_UNCHANGED)
cv2.namedWindow("test2", cv.CV_WINDOW_AUTOSIZE)
cv2.setMouseCallback("test2", a)
cv.MoveWindow("test2", 300, 300)
cv2.imshow("test2", image1)

cv2.waitKey(1000000000)


    



    