#from lishiwei import numStr
__author__ = 'zhouhang'

import cv2,os,shutil,string,fileinput,cv
import numpy as np

def ImageFillHole(Lxy, image, binImg):
    if binImg.shape != image.shape:
        binImg = np.zeros(image.shape, np.uint8)
    pts = np.zeros([Lxy.shape[0], 1, 2], np.int32)
    for i in xrange(0, Lxy.shape[0]):
        a = Lxy[i, 0], Lxy[i, 1]
        pts[i] = [[Lxy[i, 0], Lxy[i, 1]]]
    cv2.drawContours(binImg, [pts], 0, 255, cv.CV_FILLED)

def StripCorrect(binImg, image, percentage):
    image = image * (binImg / 255)
    #return image
    med = np.zeros([binImg.shape[1],1])
    for i in xrange(0, binImg.shape[1]): # col
        validLen = np.sum(binImg[:, i]) / 255
        if validLen == 0:
            med[i] = 0
            continue
        lowLen = percentage * validLen
        col = image[:, i]
        col = col[col != 0]
        col = np.sort(col)#ad
        tileMeanMin = np.mean(col[0:lowLen])
        tileMeanMax = np.mean(col[-lowLen :])
        col = np.maximum(tileMeanMin, col)
        col = np.minimum(tileMeanMax, col)
        med[i] = np.mean(col)
    greaterZeroMed = len(med > 0)
    m = np.sum(med) / greaterZeroMed
    for i in xrange(0, binImg.shape[1]):
        if med[i] > 0:
            c = m / med[i]
            image[:,i] = np.uint8(np.minimum(image[:,i] * c, 255))
    return image


#test
import TDIShaper
#Lxy = TDIShaper.ReadInitialShape('/lustre/share/Public/mostPreprocess/MBA-GF13004_compress/correct/00001.txt')
startTxt=2750
endTxt=3550
src="/lustre/share/Public/mostPreprocess/MBA-GF13004_compress/"
pre="test_"
txtSrc="/lustre/share/Public/mostPreprocess/MBA-GF13004_compress/correct/edge_sulei/"
txtPost=".txt"
post=".tif"
dst="/lustre/share/Public/mostPreprocess/MBA-GF13004_compress/correct/"
wPre="test_"
wPost="_correct.tif"
#Lxy = Lxy[:,::-1]
for x in xrange(startTxt,endTxt+1,100):
    strX="%05d"%x
    Lxy = TDIShaper.ReadInitialShape(txtSrc+strX+txtPost)
    startNum=x-49
    endNum=x+50    
    print startNum
    print endNum
    for i in xrange(startNum,endNum+1):
        iStr="%05d"%i
        fileName=src+pre+iStr+post
        image = cv2.imread(fileName,cv2.CV_LOAD_IMAGE_UNCHANGED)
#print image.shape
#print image.dtype
        print "correct "+fileName
        binImg = np.zeros(image.shape, np.uint8)
        ImageFillHole(Lxy, image, binImg)
        image1 = StripCorrect(binImg, image, 0.2)    
        cv2.imwrite(dst+wPre+iStr+wPost,image1)
#cv2.namedWindow('hehe', cv2.WINDOW_NORMAL)
#cv2.imshow('hehe', image1)
#cv2.waitKey(0)
#cv2.destroyAllWindows()


# im = cv2.imread('/home/zhouhang/1.jpg')
# imgray = cv2.cvtColor(im,cv2.COLOR_BGR2GRAY)
# imgray1 = imgray.copy()
# ret, thresh = cv2.threshold(imgray, 127, 255, 0)
# contours, hierarchy = cv2.findContours(thresh,cv2.RETR_TREE,cv2.CHAIN_APPROX_SIMPLE)
# a=contours[3]
# print(a.size)
# pts=np.array([[[50,50]],[[50,100]],[[100,50]],[[50,50]]], np.int32)
# cv2.drawContours(imgray, contours, -1, (0,255,0), 3)
# cv2.drawContours(imgray, [pts], 0, 255, cv.CV_FILLED)
# cv2.namedWindow('hehe')
# cv2.imshow('hehe',imgray)
# cv2.waitKey(0)

