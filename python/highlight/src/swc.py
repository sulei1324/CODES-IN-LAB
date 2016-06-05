__author__ = 'Su Lei'

import numpy as np
import math
import time
import cv2 as cv
from subBackground import subBackground

swcType = np.dtype({
                       'names': ['serial', 'nodeTye', 'x', 'y', 'z', 'r', 'parentSerial'],
                       'formats': [np.int, np.int, 'f', 'f', 'f', 'f', 'i']
                   }, align=True)


def readSwc(filename):
    f = open(filename)
    swcNum = []
    for eachLine in f:
        tmpStr = eachLine.strip().split(' ')
        tmpNum = []
        for i in xrange(len(tmpStr)):
            if i == 0 or i == 1 or i == 6:
                tmpNum.append(int(tmpStr[i]))
            elif i == 2 or i == 3:
                tmpNum.append(float(tmpStr[i]) * 10 / 3)
            else:
                tmpNum.append(float(tmpStr[i]))
        swcNum.append(tmpNum)
    return swcNum


def readSwcNp(filename):
    f = open(filename)
    swc = []
    for eachLine in f:
        tmpStr = eachLine.strip().split(' ')
        tmpNum = []
        for i in xrange(len(tmpStr)):
            if i is 0 or i is 1 or i is 6:
                tmpNum.append(int(tmpStr[i]))
            else:
                tmpNum.append(float(tmpStr[i]))
        swc.append(tmpNum)
    swcNp = np.array([], dtype=swcType)
    for i in xrange(len(swc)):
        tmpSwcNp = np.array(tuple(swc[i]), dtype=swcType)
        swcNp = np.append(tmpSwcNp, swcNp)
    return swcNp


def cmpAsZ(x, y):
    if x[2] > y[2]:
        return 1
    else:
        return -1


def trimSwc(s):
    while s[len(s) - 1][6] is -1:
        s.pop(len(s) - 1)
        if len(s) is 0:
            break
    pass


def convert2line(s):
    sn = len(s)
    if sn == 0:
        exit()
    lines = []
    i = 0
    for col in s:
        if col[6] != col[0] - 1:
            if i is not 0:
                lines.append(tmp)
            tmp = []
        tmp.append(col)
        if i == sn - 1:
            lines.append(tmp)
        i += 1
    return lines


def printLineHeadAndTail(ls):
    for i in xrange(len(ls)):
        lineLength = len(ls[i])
        head = (ls[i][0][0], ls[i][0][6])
        tail = (ls[i][lineLength - 1][0], ls[i][lineLength - 1][6])
    print head, tail


def distanceOf2p(p1, p2):
    return math.sqrt((p1[0] - p2[0]) ** 2 + (p1[1] - p2[1]) ** 2 + (p1[2] - p2[2]) ** 2)


def insertLines(ls, minDistance):
    coordinatesOfLines = []
    for i in xrange(len(ls)):
        line = ls[i]
        coordinatesOfLine = []
        for j in xrange(len(line) - 1):
            cp = line[j]
            np = line[j + 1]
            d = distanceOf2p((cp[2], cp[3], cp[4]), (np[2], np[3], np[4]))
            if d <= minDistance:
                coordinatesOfLine.append([cp[2], cp[3], cp[4]])
            else:
                coordinatesOfLine.append([cp[2], cp[3], cp[4]])
                insertedNumOfP = int(math.ceil(d / minDistance))
                slopeOfX = (np[2] - cp[2]) / (insertedNumOfP + 1)
                slopeOfY = (np[3] - cp[3]) / (insertedNumOfP + 1)
                slopeOfZ = (np[4] - cp[4]) / (insertedNumOfP + 1)
                for k in xrange(insertedNumOfP):
                    cx = cp[2] + slopeOfX * (k + 1)
                    cy = cp[3] + slopeOfY * (k + 1)
                    cz = cp[4] + slopeOfZ * (k + 1)
                    print [cx, cy, cz]
                    coordinatesOfLine.append([cx, cy, cz])
            if j == (len(line) - 2):
                coordinatesOfLine.append([np[2], np[3], np[4]])
        coordinatesOfLines.append(coordinatesOfLine)
    return coordinatesOfLines


def getBallCordinates(r):
    ballCordinates = []
    for i in xrange(-r, r + 1):
        for j in xrange(-r, r + 1):
            for k in xrange(-r, r + 1):
                if i ** 2 + j ** 2 + k ** 2 <= r ** 2:
                    ballCordinates.append((i, j, k))
    return ballCordinates


def getAllCordinates(ls, r, width, height, zRange):
    allCordinates = []
    ballCor = getBallCordinates(r)
    time.clock()
    for i in xrange(len(ls)):
        line = ls[i]
        print i + 1, ' of ', len(ls), ' ', len(line), ' ', time.clock()
        for j in line:
            cx, cy, cz = j
            for k in ballCor:
                x0 = int(cx) + k[0]
                y0 = int(cy) + k[1]
                z0 = int(cz) + k[2]
                if x0 < 0 or y0 < 0 or z0 < zRange[0]:
                    continue
                if x0 >= width or y0 >= height or z0 >= zRange[1]:
                    continue
                allCordinates.append((x0, y0, z0))
        allCordinates = list(set(tuple(allCordinates)))
    allCordinates.sort(cmpAsZ)
    return np.array(allCordinates)


def getArea(a):
    return ((min(a[:, 0]), max(a[:, 0])),
            (min(a[:, 1]), max(a[:, 1])), (min(a[:, 2]), max(a[:, 2])))


def groupByZ(a, zRange):
    zS = zRange[0]
    zE = zRange[1]
    groups = []
    j = 0
    for i in xrange(zS, zE + 1):
        tmp = []
        while j < len(a):
            if a[j, 2] == i:
                tmp.append(a[j])
                j += 1
            else:
                break
        groups.append(tmp)
    return groups


def doHighlight(area, width, height, src, dst, pre, post, write_pre, write_post, points, doSub):
    (out_x_start, out_x_end), (out_y_start, out_y_end), (out_z_start, out_z_end) = area
    zRange = out_z_end - out_z_start + 1
    for i in xrange(zRange):
        pointsInThisZ = points[i]
        zSerial = pointsInThisZ[0][2]
        readImageName = src + pre + '%05d' % zSerial + post
        writeImageName = dst + write_pre + '%05d' % i + write_post
        print readImageName
        print writeImageName
        if i == 0:
            inImage = cv.imread(readImageName, cv.CV_LOAD_IMAGE_UNCHANGED)
            tmpImage = inImage[out_y_start: out_y_end + 1, out_x_start: out_x_end + 1]
            outImage = np.zeros((out_y_end - out_y_start + 1, out_x_end - out_x_start + 1), np.uint8)
            if doSub:
                subBackground(tmpImage)
#             for j in pointsInThisZ:
#                 x = pointsInThisZ[j][0]
#                 y = pointsInThisZ[j][1]
#                 outImage[y, x] = tmpImage[y, x]
            outImage = tmpImage
            cv.imwrite(writeImageName, outImage)
        else:
            break

# if __name__ == '__main__':
# outSwcNum = readSwc('test.swc')
#     trimSwc(outSwcNum)
#     linesInSwc = convert2line(outSwcNum)
#     insertedLines = insertLines(linesInSwc, 5)
#     allPoints = getAllCordinates(insertedLines, 10)
#     highlightArea = getArea(allPoints)
#     pointsGroupedByZ = groupByZ(allPoints, (highlightArea[2][0], highlightArea[2][1]))

# for zPoints in pointsGroupedByZ:
#     z = zPoints[0][2]
#     f = open('.\pointsGroupedByZ\z' + str(z) + '.swc', 'w')
#     for i in xrange(len(zPoints)):
#         t = zPoints[i]
#         t = list(t)
#         t.append('\n')
#         f.writelines(' '.join([str(x) for x in t]))
#     f.close()
# fo = open('test2.swc', 'w')
# ind = 0
# for i in xrange(len(allPoints)):
#     t = allPoints[i]
#     t = list(t)
#     t.append('\n')
#     fo.writelines(' '.join([str(x) for x in t]))
#     ind += 1
# fo.close()
# print ind









