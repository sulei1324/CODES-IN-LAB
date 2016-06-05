__author__ = 'zhouhang'
import numpy as np

import cv2,os,shutil,string,cv
import numpy as np

def normalized(a, axis=-1):
    return a / max(0.0001, np.linalg.norm(a))

def ReadInitialShape(fileName):#fileName = "'/home/zhouhang/TDI/lj/test_txt/test_03048.txt'"
    shapeFp = open(fileName, "r")
    lines = shapeFp.readlines()
    allLine = []
    for line in lines:
        if line[0] == '#' or line[0] == '\n':
            continue
        allLine.append(line.replace('\n','').split(' '))
    shapeFp.close()
    Lxy = np.zeros([len(allLine), 2],np.float64)
    index = 0
    for item in allLine:
        Lxy[index, 0] = string.atof(item[0])
        Lxy[index, 1] = string.atof(item[1])
        index = index + 1
    return Lxy

def SegmentedFuncFit(ray):
    ray = np.minimum(ray, 20)
    nx = len(ray)
    hnx = round(np.double(nx) / 2)
    lx = 20
    maxVal = np.mean(ray[(lx-1):(hnx - lx)]) #may be wrong
    minVal = np.mean(ray[(hnx + lx - 1):(-1 - lx + 1)])
    fitError = (10 ** 5) * np.ones([nx, 1],np.float64)
    for i in xrange(1, nx):
        fitRay = np.hstack((maxVal * np.ones([1, i + 1],np.float64), minVal * np.ones([1, nx - i - 1],np.float64)))
        fitError[i] = np.linalg.norm(ray - fitRay)
    idxMinError = np.argmin(fitError)
    idexxS = np.arange(0, nx)
    smooth_diff_ray = np.exp(-0.005 * (( idexxS - idxMinError ) ** 2))
    return smooth_diff_ray

def SmoothGrad_Fit( SphereXX ):
    [nx, ny] = SphereXX.shape
    Uz = np.zeros([nx, ny],np.float64)
    for i in xrange( 0, nx):
        smooth_diff_ray = SegmentedFuncFit(SphereXX[i,:] )
        Uz[i, 0:len(smooth_diff_ray)] = smooth_diff_ray
    return Uz

def ShapeFit(img, Lxy):
    Lx = Lxy[:, 0]
    Ly = Lxy[:, 1]
    [nx, ny] = img.shape
    Theta = 360
    Leng = 100
    SphereXX_r = np.zeros([Theta+2 , 2*Leng+1], np.float64 )
    SphereXX_x = np.zeros(SphereXX_r.shape, np.float64)
    SphereXX_y = np.zeros(SphereXX_r.shape, np.float64)
    bsize = 2
    G = np.ones([2 * bsize + 1, 2*bsize +1], np.float64) / (2 * bsize + 1)
    Direction = np.zeros([1,2], np.float64)

    for i in xrange(1, Theta + 1):#end + 1 has been -1
        Direction = [Ly[i + 1] - Ly[i - 1], -(Lx[i +1] - Lx[i - 1])]
        Direction = normalized(Direction)
        zdXX = 0
        fdXX = 0
        for ii in xrange(1, 30 + 1):
            zdXX = zdXX + float(img[max(min(round(Lx[i]+10*ii*Direction[0]),nx-1),0), max(min(round(Ly[i]+10*ii*Direction[1]), ny-1), 1)])
            fdXX = fdXX + float(img[max(min(round(Lx[i]-10*ii*Direction[0]),nx-1),0), max(min(round(Ly[i]-10*ii*Direction[1]), ny-1), 1)])
        if zdXX > fdXX:
            Direction = -Direction
        tmpImg = np.zeros([2*bsize+1,2*bsize+1],np.float64)
        for j in xrange(-Leng, Leng + 1) :
            Piont = 2*j*Direction + [ Lx[i], Ly[i] ]

            idxx = [x for x in xrange(
                max( min(np.int(round(Piont[0]-bsize)), nx -1), 0 ),
                               max( min(np.int(round(Piont[0]+bsize)), nx-1) , 0 ) + 1)]
            idxy = [x for x in xrange(
                max( min(np.int(round(Piont[1]-bsize)), ny -1), 0 ),
                max( min(np.int(round(Piont[1]+bsize)), ny-1), 0 ) + 1)]

            tmpImg = np.array(img[idxx[0]:(idxx[-1]+1), idxy[0]:(idxy[-1]+1)], np.float64) # has been copied
            SphereXX_r[i, j + Leng] = np.mean(tmpImg)

            SphereXX_x[ i , j+Leng ] = Piont[0]
            SphereXX_y[ i , j+Leng ] = Piont[1]

    SphereXX_r[0,: ] = SphereXX_r[Theta,: ]
    SphereXX_r[Theta + 1,: ] = SphereXX_r[1,: ]
    SphereXX_x[0,: ] = SphereXX_x[Theta ,: ]
    SphereXX_x[Theta + 1,: ] = SphereXX_x[1,: ]
    SphereXX_y[0,: ] = SphereXX_y[Theta,: ]
    SphereXX_y[Theta + 1,: ] = SphereXX_y[1,: ]

    Uz = SmoothGrad_Fit(SphereXX_r[1:Theta+1,:])
    Ur = (Leng+1)*np.ones([Theta+2, 1], np.float64)
    Ur0 = Ur.copy()#!!!!warning
    idexxS = np.arange(1.0, np.float64((2*Leng+1) + 1))
    for kk in xrange(0, 100):
        for i in xrange(1, Theta+1):
            pp0 = Ur[i]
            TT = Uz[i-1, :]
            JJt = TT * np.exp(-0.005*(idexxS-pp0)**2)
            Ur[i] = Ur[i] + 0.3*(np.sum(idexxS*JJt)/np.sum(JJt)-Ur[i]) - 0.7*(2*Ur[i]-Ur[i-1]-Ur[i+1])
            Ur = np.minimum(np.maximum(Ur, Ur0-4), Ur0+4)
            Ur = np.minimum(np.maximum(Ur, 1), 2*Leng+1)
            Ur[0] = Ur[Theta]
            Ur[Theta+1] = Ur[1]
    LxyNew = np.zeros(Lxy.shape, np.float64)
    for i in xrange(0, Theta + 2):
        LxyNew[i, 0] = SphereXX_x[i, np.int(round(Ur[i]) - 1)]
        LxyNew[i, 1] = SphereXX_y[i, np.int(round(Ur[i]) - 1)]
    return LxyNew

def Smooth(ray, N):
    L = ray
    nL = len(L)
    for i in xrange(0, N):
        L[0] = 0.5*(L[0] + L[1])
        for j in xrange(1, nL - 1):
            L[j] = 0.3333333*(L[j-1] + L[j] + L[j+1])
        L[nL-1] = 0.5*(L[nL-1] + L[nL-2])
    return L

def ImageDrawContour(Lxy, image):
    pts = np.zeros([Lxy.shape[0], 1, 2], np.int32)
    for i in xrange(0, Lxy.shape[0]):
        a = Lxy[i, 0], Lxy[i, 1]
        pts[i] = [[Lxy[i, 0], Lxy[i, 1]]]
    cv2.drawContours(image, [pts], 0, [255,255,255],10)#, cv.CV_FILLED
    return img

#test
#Lxy = ReadInitialShape('/home/zhouhang/TDI/lj/test_txt/test_03048.txt')
#Lxy = Lxy - 1
#Lxy = Lxy[:,::-1]
#readPre = "/home/zhouhang/TDI/lj/text/test_"
#readPost = ".tif"
# img = cv2.imread(readPre + "03048" + readPost)
# img = ImageDrawContour(Lxy[:,::-1], img)
# cv2.namedWindow('hehe', cv2.WINDOW_NORMAL)
# cv2.imshow('hehe', img)
# cv2.waitKey(0)
# cv2.destroyAllWindows()
#begNum = 3049
#endNum = 3060
#for z in xrange(begNum, endNum + 1):
#    print "processing %d"%z
#    img = cv2.imread(readPre + "%05d"%z + readPost, cv2.CV_LOAD_IMAGE_UNCHANGED)
#    LxyNew = ShapeFit(img, Lxy)
#    Lx = Smooth(LxyNew[:,0],1)
#    Ly = Smooth(LxyNew[:,1],1)
#    Lxy = np.hstack((Lx.reshape(Lx.shape[0],1), Ly.reshape(Ly.shape[0],1)))
#    if z == endNum:
#        img = ImageDrawContour(Lxy[:,::-1], img)
#        cv2.namedWindow('hehe', cv2.WINDOW_NORMAL)
#        cv2.imshow('hehe', img)
#        cv2.waitKey(0)
#        cv2.destroyAllWindows()
