import cv2, numpy as np
import sys, os
import cv,string,shutil
import findLostFile as flf
import allocateNum as aN

def montage(usedArray,imPre,imPost,dstFile):
    src ="G:\\sulei\\13004\\test\\"
    readPre = "test_"
    readPost = ".jpg"
    dst = "G:\\sulei\\13004\\test\\00949s\\"
    writePre = "test_"
    writePost = "python.tif"
    begNum = 949       #input("Please input begin num\n")
    endNum = 949    # input("Please input end num\n")
    xBeg = 40         # input("xBeg:\n")
    xEnd = 57         # input("xEnd:\n")
    yBeg = 31        # input("yBeg:\n")
    yEnd = 53        # input("yEnd:\n")
    isReverse = 1   # input("is reverse?1:0\n")
      
    numStr = "%05d"%(sA[0])
    xStr = "%d"%(xBeg)
    yStr = "%d"%(yBeg)
    filename = src + numStr + "\\" + readPre + numStr +"_" + xStr + "_" + yStr + readPost
    
    subimg = cv2.imread(filename,cv2.CV_LOAD_IMAGE_UNCHANGED)
    xWidth = subimg.shape[0]
    yWidth = subimg.shape[1]
    img = np.zeros((subimg.shape[0]*(yEnd-yBeg+1),subimg.shape[1]*(xEnd-xBeg+1)),np.uint8)
    
    
    for z in range(len(sA)):
        s = sA[z]
        numStr = "%05d"%(s)
        print "processing " + writePre + numStr + writePost
        for i in xrange(yBeg,yEnd+1):
            for j in xrange(xBeg,xEnd+1):
                yStr = "%d"%(i)
                xStr = "%d"%(j)
                filename = src + numStr + "/" + readPre + numStr + "_" + xStr + "_" + yStr + readPost
                subimg = cv2.imread(filename,cv2.CV_LOAD_IMAGE_UNCHANGED)
                if isReverse == 0:
                    img[(i-yBeg)*xWidth:(i+1-yBeg)*xWidth,(j-xBeg)*yWidth:(j+1-xBeg)*yWidth] = subimg
                if isReverse == 1:
                    subimg = subimg[:,::-1]
                    img[(i-yBeg)*xWidth:(i+1-yBeg)*xWidth,(j-xBeg)*yWidth:(j+1-xBeg)*yWidth] = subimg
                cv2.imwrite(dst + writePre + numStr + '-' + xStr +  '-'  + yStr + writePost,img)
        cv2.imwrite(dst + writePre + numStr + writePost,img)
