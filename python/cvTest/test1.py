import cv2.cv as cv
import numpy
from cv2 import pyrUp, CV_LOAD_IMAGE_UNCHANGED
import cv2
src = cv2.imread(r"G:\sulei\workplace\cvTest\GFP_4281-4370.tif", CV_LOAD_IMAGE_UNCHANGED)
cv2.namedWindow("pyrDown")
i = 0
while src.shape[0] != 1:
    src = cv2.pyrDown(src)
    print src.shape
    cv2.imshow("pyrDown",  src)
    cv2.imwrite("%d.tif"%i, src)
    i += 1
    cv2.waitKey(300)