__author__ = 'Su Lei'

import cv2 as cv
import numpy as np
import math
import opsOfSub as op
from copy import deepcopy
import time


def subBackground(inImage):
    raw_image = inImage
    raw_image = np.float32(raw_image)

    height, width = raw_image.shape
    radius = 50
    ball, shrinkFactor = op.createRollingBall(radius)
    shrink = shrinkFactor > 1

    op.filter3x3(raw_image, 'mean')
    smoothed_image = deepcopy(raw_image)
    minmax = op.getMinMax(smoothed_image)

    if shrink:
        smallImage = op.shrinkImage(smoothed_image, shrinkFactor)
    else:
        smallImage = smoothed_image

    op.rollBall(ball, smallImage)
    outImage = op.enlargeImage(smallImage, height, width, shrinkFactor)
    outImage = np.uint8(outImage)
    raw_image = np.uint8(raw_image)
    outImage = raw_image - outImage
    return outImage





if __name__ == '__main__':
     raw_image = cv.imread('G:\\sulei\\workplace\\Swc\\test\\1.tif', cv.CV_LOAD_IMAGE_UNCHANGED)
     raw_image = np.float32(raw_image)
     t1 = time.time()
     height, width = raw_image.shape
     radius = 50
     ball, shrinkFactor = op.createRollingBall(radius)
     shrink = shrinkFactor > 1
     op.filter3x3(raw_image, 'mean')
     smoothed_image = deepcopy(raw_image)
     minmax = op.getMinMax(smoothed_image)
     if shrink:
         smallImage = op.shrinkImage(smoothed_image, shrinkFactor)
     else:
         smallImage = smoothed_image
         
     op.rollBall(ball, smallImage)
#     cv.imwrite('2.tif', smallImage)
     outImage = op.enlargeImage(smallImage, height, width, shrinkFactor)
     outImage = np.uint8(outImage)
#     cv.imwrite('3.tif', outImage)
     raw_image = np.uint8(raw_image)
     outImage = raw_image - outImage
     t2 = time.time()
     print 'main: ', t2 - t1
     cv.imwrite('2.tif', outImage)