__author__ = 'Su Lei'

import cv2 as cv
import numpy as np
import math
import time


def createRollingBall(r):
#    t1 = time.time()
    if r <= 10:
        shrinkFactor = 1
        arcTrimPer = 24
    elif r <= 30:
        shrinkFactor = 2
        arcTrimPer = 24
    elif r <= 100:
        shrinkFactor = 4
        arcTrimPer = 32
    else:
        shrinkFactor = 8
        arcTrimPer = 40
    smallballradius = r * 1.0 / shrinkFactor
    if smallballradius < 1:
        smallballradius = 1
    rsquare = smallballradius * smallballradius
    xtrim = arcTrimPer * smallballradius / 100
    halfWidth = math.floor(smallballradius - xtrim)
    width = halfWidth * 2 + 1
    width = int(width)
    data = np.zeros((width, width))
    for i in xrange(width):
        for j in xrange(width):
            xval = j - halfWidth
            yval = i - halfWidth
            temp = rsquare - xval * xval - yval * yval
            temp = np.float32(temp)
            if temp > 0:
                data[i, j] = math.sqrt(temp)
            else:
                data[i, j] = 0
#    t2 = time.time()
#    print 'createRollingBall:', t2 - t1
    return data, shrinkFactor


def filter3(inImage, s, n, t):
#    t1 = time.time()
    i = 0
    if s == 'row':
        y_ini = n
        x_ini = 0
        l = inImage.shape[1]
    else:
        y_ini = 0
        x_ini = n
        l = inImage.shape[0]
    v3 = inImage[y_ini, x_ini]
    v2 = v3
    while i < l:
        v1 = v2
        v2 = v3
        if i < l - 1:
            if s == 'row':
                v3 = inImage[y_ini, x_ini + 1]
            else:
                v3 = inImage[y_ini + 1, x_ini]
        if t == 'MAXIMUM':
            if v1 > v3:
                max1 = v1
            else:
                max1 = v3
            if v2 > max1:
                max1 = v2
            inImage[y_ini, x_ini] = max1
        else:
            inImage[y_ini, x_ini] = (v1 + v2 + v3) * 1 / 3
        if s == 'row':
            x_ini += 1
        else:
            y_ini += 1
        i += 1
#    t2 = time.time()
#    print 'filter3:', t2 - t1


def filter3x3(inImage, type1):
#    t1 = time.time()
    height, width = inImage.shape
    for y in xrange(height):
        filter3(inImage, 'row', y, type1)
    for x in xrange(width):
        filter3(inImage, 'column', x, type1)
#    t2 = time.time()
#    print 'filter3x3:', t2 - t1


def getMinMax(inImage):
#    t1 = time.time()
    min1 = 256
    max1 = -1
    y, x = inImage.shape
    for i in xrange(y):
        for j in xrange(x):
            if inImage[i, j] > max1:
                max1 = inImage[i, j]
            elif inImage[i, j] < min1:
                min1 = inImage[i, j]
#    t2 = time.time()
#    print 'getMinMax:', t2 - t1
    return min1, max1


def shrinkImage(inImage, f):
#    t1 = time.time()
    height, width = inImage.shape
    sWidth = (width + f - 1) / f
    sHeight = (height + f - 1) / f
    smallImage = np.zeros((sHeight, sWidth))
    for ySmall in xrange(sHeight):
        for xSmall in xrange(sWidth):
            min1 = 256
            j = 0
            y = f * ySmall
            while j < f and y < height:
                k = 0
                x = f * xSmall
                while k < f and x < width:
                    thispixel = inImage[y, x]
                    if thispixel < min1:
                        min1 = thispixel
                    k += 1
                    x += 1
                j += 1
                y += 1
            smallImage[ySmall, xSmall] = min1
#    t2 = time.time()
#    print 'shrinkImage:', t2 - t1
    return smallImage


def rollBall(b, inImage):
#    t1 = time.time()
    height, width = inImage.shape
    ballWidth = b.shape[0]
    radius = ballWidth / 2
    cache = np.zeros((ballWidth, width))
    y = -radius
    while y < height + radius:
        nextLineToWriteInCache = (y + radius) % ballWidth
        nextLineToRead = y + radius
        if nextLineToRead < height:
            cache[nextLineToWriteInCache, :] = inImage[nextLineToRead, :]
            x = 0
            p = nextLineToRead
            while x < width:
                inImage[p, x] = -100000
                x += 1
        y0 = y - radius
        if y0 < 0:
            y0 = 0
        yBall0 = y0 - y + radius
        yEnd = y + radius
        if yEnd > height - 1:
            yEnd = height - 1
        x = -radius
        while x < width + radius:
            z = 256
            x0 = x - radius
            if x0 < 0:
                x0 = 0
            xBall0 = x0 - x + radius
            xEnd = x + radius
            if xEnd > width - 1:
                xEnd = width - 1
            yp = y0
            yBall = yBall0
            while yp <= yEnd:
                cachePointer = yp % ballWidth
                xp = x0
                bp = xBall0
                while xp <= xEnd:
                    zReduced = cache[cachePointer, xp] - b[yBall, bp]
                    if z > zReduced:
                        z = zReduced
                    xp += 1
                    bp += 1
                yp += 1
                yBall += 1
            yp = y0
            yBall = yBall0
            while yp <= yEnd:
                xp = x0
                bp = xBall0
                while xp <= xEnd:
                    zMin = z + b[yBall, bp]
                    if inImage[yp, xp] < zMin:
                        inImage[yp, xp] = zMin
                    xp += 1
                    bp += 1
                yp += 1
                yBall += 1
            x += 1
        y += 1
#    t2 = time.time()
#    print 'rollBall:', t2 - t1


def makeInterpolationArrays(indices, w, l, sl, f):
    for i in xrange(l):
        smallIndex = ((i - (f / 2)) / f)
        if smallIndex < 0:
            smallIndex = 0
        if smallIndex >= sl - 1:
            smallIndex = sl - 2
        indices[i] = smallIndex
        distance = (i + 0.5) / f - (smallIndex  + 0.5)
        w[i] = 1.0 - distance
#    print w


def enlargeImage(inImage, h, w, f):
#    t1 = time.time()
    height, width = h, w
    smallHeight, smallWidth = inImage.shape
    outImage = np.zeros((height, width))
    xSmallIndices = np.zeros(width)
    xWeights = np.zeros(width)
    makeInterpolationArrays(xSmallIndices, xWeights, width, smallWidth, f)
#     print xSmallIndices
#     print xWeights
    ySmallIndices = np.zeros(height)
    yWeights = np.zeros(height)
    makeInterpolationArrays(ySmallIndices, yWeights, height, smallHeight, f)
    line0 = np.zeros(width)
    line1 = np.zeros(width)
    for x in xrange(width):
        line1[x] = inImage[0, xSmallIndices[x]] * xWeights[x] + \
                   inImage[0, xSmallIndices[x] + 1] * (1 - xWeights[x])
    ySmallLine0 = -1
    for y in xrange(height):
        if ySmallLine0 < ySmallIndices[y]:
            swap = line0
            line0 = line1
            line1 = swap
            ySmallLine0 += 1
            sYPointer = ySmallIndices[y] + 1
            for x in xrange(width):
                line1[x] = inImage[sYPointer, xSmallIndices[x]] * \
                           xWeights[x] + inImage[sYPointer, xSmallIndices[x] + 1] * \
                                         (1 - xWeights[x])
        weight = yWeights[y]
        for x in xrange(width):
            outImage[y, x] = line0[x] * weight + line1[x] * (1 - weight)
#    t2 = time.time()
#    print 'enlargeImage:', t2 - t1
    return outImage

