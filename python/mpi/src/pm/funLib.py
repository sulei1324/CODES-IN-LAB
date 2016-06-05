import os
import re
import numpy as np
import sys
from numpy.core.multiarray import dtype
import tarfile
import cv2
import cv,string,shutil


class Data_info():
    def __init__(self, filename):
        self.filename = filename
        self.nodes_names = None
        self.process_num = -1
        self.src = None
        self.dst = None
        self.begin_num = -1
        self.end_num = -1
        self.is_projection = -1
        self.thick_projection = -1
        self.is_resampling = -1
        self.reciprocal_scale = None
        self.get_info()
    
    def get_info(self):
        data_file = open(self.filename, 'r')
        i = 0
        for line in data_file:
            if i == 1:
                self.nodes_names = line.strip()
            if i == 3:
                self.process_num = int(line.strip())
            if i == 5:
                self.src = line.strip()
            if i == 7:
                self.dst = line.strip()
            if i == 9:
                self.begin_num = int(line.strip())
            if i == 11:
                self.end_num = int(line.strip())
            if i == 13:
                self.is_projection = bool(int(line.strip()))
            if i == 15:
                self.thick_projection = int(line.strip())
            if i == 17:
                self.is_resampling = bool(int(line.strip()))
            if i == 19:
                self.reciprocal_scale = [int(j) for j in line.strip().split(' ')]
            i += 1
        data_file.close()
        








def newState(nodeName,n,pType,mType):
    t = pType
    if t == 1:
        appName = "tar2monApp.py"
    elif t == 2:
        appName = "tar2proApp.py"
    elif t == 3:
        appName = "tar2resApp.py"
    nodeArray = nodeName.split()
    nodeNum = len(nodeArray)
    if mType == 1:
        
        mpiState = "/usr/mpi/gcc/openmpi-1.4.3/bin/mpirun -n "
        s=str(n)
        mpiState = mpiState + s + ' '     
        s = ""
        for i in range(len(nodeArray)):
            s = s + "-host " + nodeArray[i] + " "       
        mpiState = mpiState + s + "python "      

        mpiState = mpiState + appName
    else:
        mpiState = "mpiexec.exe "
        s = str(n)
        mpiState += "-hosts " + s + " " + nodeName + ' python ' + appName
        
    return mpiState



def createFile(n,t):
    dstRoot = "G:\\sulei\\workplace\\mpi\\src\\test\\result\\"
    dstFile = dstRoot + n
    if os.path.exists(dstFile):
        return False
    else:
        os.makedirs(dstFile)
        dstTarFile  = dstFile + "\\" +"src" 
        os.makedirs(dstTarFile)
        if t == 1:                      
            dstMonFile = dstFile + "\\" +"montage"            
            os.makedirs(dstMonFile)
        if t == 2:
            dstMonFile = dstFile + "\\" +"montage"            
            os.makedirs(dstMonFile)
            dstProFile =  dstFile + "\\" +"project"                
            os.makedirs(dstProFile)
        if t == 3:
            dstMonFile = dstFile + "\\" +"montage"            
            os.makedirs(dstMonFile)
            dstProFile =  dstFile + "\\" +"project"                
            os.makedirs(dstProFile)            
            dstResFile =  dstFile + "\\" +"resize"                
            os.makedirs(dstResFile)                    
        return True
        
def getLevlRange(s):
    srcFile = s
    levelMax = 0
    levelMin = 0
    levelLong  = 0
    fileList = os.listdir(srcFile)
    print fileList
    for i in fileList:
        j = re.match("^(\d\d\d\d\d)\.tar$", i)
        if j == None:
            continue
        else:
            levelLong = levelLong + 1
            levelStr = j.group(1)
            levelNum = int(levelStr)
            if levelLong == 1:
                levelMax = levelNum
                levelMin = levelNum
            else:
                if levelNum > levelMax:
                    levelMax = levelNum
                elif levelNum < levelMin:
                    levelMin = levelNum
    
    return (levelMin,levelMax)
                    

def hasLost(begNum,endNum,srcPath,readPre,readPost):
    for i in range(begNum,endNum+1):
        serialN = "%05d"%(i)
        filename = srcPath + readPre + serialN +readPost
        if os.path.exists(filename):        
            pass
        else:
            return True

    
def printLostFile(begNum,endNum,srcPath,readPre,readPost):
    lostFileN=0
    existFileN=0
    lostFileSA = []
    existFileSA =[]
    sExistSN = None
    eExistSN = None
    sLostSN = None
    eLostSN = None
    for i in range(begNum,endNum+1):
        serialN = "%05d"%(i)
        filename = srcPath + readPre + serialN +readPost
        if os.path.exists(filename):        
            existFileN+=1
            if existFileN == 1:
                sExistSN = i
                eExistSN = i
            else:
                if (i - eExistSN) == 1:
                    eExistSN = i
                else:
                    preExistSA = [sExistSN,eExistSN]
                    sExistSN = i    
                    eExistSN = i
                    existFileSA += preExistSA 
        else:
            lostFileN+=1
            if lostFileN ==1:            
                sLostSN = i
                eLostSN = i
            else:
                if (i - eLostSN) == 1:
                    eLostSN = i
                else:
                    preLostSA = [sLostSN,eLostSN]
                    sLostSN = i
                    eLostSN = i
                    lostFileSA += preLostSA
        if i == endNum:
            if (eLostSN != None) and (eLostSN <= endNum):
                preLostSA = [sLostSN,eLostSN]
                lostFileSA+=preLostSA
            if (eExistSN != None) and (eExistSN <= endNum):
                preExistSA = [sExistSN,eExistSN]
                existFileSA += preExistSA 
    
    if lostFileN == 0:
        print "There is no file lost."
    else:
        print "The files below are missing: "
        for i in range(len(lostFileSA)//2):
            s = lostFileSA[2*i]
            e = lostFileSA[2*i+1]
            for j in range(s,e+1):
                serialN = "%05d"%(j)
                filename = srcPath + readPre + serialN +readPost
                print filename
    
    

    


def getAvailSerial(begNum,endNum,srcPath,readPre,readPost):
    lostFileN=0
    existFileN=0
    lostFileSA = []
    existFileSA =[]
    sExistSN = None
    eExistSN = None
    sLostSN = None
    eLostSN = None
    for i in range(begNum,endNum+1):
        serialN = "%05d"%(i)
        filename = srcPath + readPre + serialN +readPost
        if os.path.exists(filename):        
            existFileN+=1
            if existFileN == 1:
                sExistSN = i
                eExistSN = i
            else:
                if (i - eExistSN) == 1:
                    eExistSN = i
                else:
                    preExistSA = [sExistSN,eExistSN]
                    sExistSN = i    
                    eExistSN = i
                    existFileSA += preExistSA 
        else:
            lostFileN+=1
            if lostFileN ==1:            
                sLostSN = i
                eLostSN = i
            else:
                if (i - eLostSN) == 1:
                    eLostSN = i
                else:
                    preLostSA = [sLostSN,eLostSN]
                    sLostSN = i
                    eLostSN = i
                    lostFileSA += preLostSA
        if i == endNum:
            if (eLostSN != None) and (eLostSN <= endNum):
                preLostSA = [sLostSN,eLostSN]
                lostFileSA+=preLostSA
            if (eExistSN != None) and (eExistSN <= endNum):
                preExistSA = [sExistSN,eExistSN]
                existFileSA += preExistSA 
    
    
    usedFileSerial = [0]*existFileN
    if existFileN == 0:
        return None
    else:
        index = 0        
        for i in range(len(existFileSA)//2):
            s = existFileSA[2*i]
            e = existFileSA[2*i+1]
            for j in range(s,e+1):
                usedFileSerial[index] = j
                index += 1
        return usedFileSerial


def alloNum(s,usedArray):
        alloedArray=[]
        l = len(usedArray)
        drawerN = l/s
        lastBall = l%s
        longList = [drawerN]*s
        if lastBall == 0:
            pass
        else:
            for i in range(lastBall):
                longList[i] = longList[i] + 1
        index = 0
        for i in range(s):
            l = longList[i]
            tA = usedArray[index:l+index]
            alloedArray.append(tA)
            index = l + index
        
        return alloedArray
                           

def alloNum4pro(s,usedArray,n):
        alloedArray=[]
        l = len(usedArray)
        workN = l / n
        lastWork = l % n
        drawerN = workN / s
        lastBall = workN % s
        longList = [drawerN*n]*s
        if lastBall == 0:
            pass
        else:
            for i in range(lastBall):
                longList[i] = longList[i] + n
        if lastWork != 0:
            longList[s-1] = longList[s-1] + lastWork
        index = 0
        for i in range(s):
            l = longList[i]
            tA = usedArray[index:l+index]
            alloedArray.append(tA)
            index = l + index
         
        return alloedArray    

def getFrameIm(s,n):
    src = s
    numStr = "%05d"%n
    nFileSrc = src + numStr +"\\"
    fileList = os.listdir(nFileSrc)
    p = r"test_(\d\d\d\d\d)_(\d\d)_(\d\d).jpg"
    getFlag = 0
    xBeg = 0
    yBeg = 0
    xEnd = 0
    yEnd = 0
    for i in fileList:
        m = re.match(p, i)
        if m != None:
            if getFlag == 0:
                getFlag = 1
                xBeg = m.group(2)
                xEnd = m.group(2)
                yBeg = m.group(3)
                yEnd = m.group(3)  
            else:
                if m.group(2) > xEnd:
                    xEnd = m.group(2)
                elif m.group(2)<xBeg:
                    xBeg = m.group(2)
                if m.group(3) > yEnd:
                    yEnd = m.group(3)
                elif m.group(3) < yBeg:
                    yBeg = m.group(3)
                        

    if getFlag == 0:
        return None
    else:
        return (xBeg,xEnd,yBeg,yEnd)



def montage(usedArray,s,d):
    src = s
    readPre = "test_"
    readPost = ".jpg"
    dst = d
    sA  = usedArray 
    print sA
    writePre = "test_"
    writePost = "_mon.tif"
    frameIm = getFrameIm(src,sA[0])
    xBeg = int(frameIm[0])        # input("xBeg:\n")
    xEnd = int(frameIm[1])             # input("xEnd:\n")
    yBeg = int(frameIm[2])             # input("yBeg:\n")
    yEnd = int(frameIm[3])           # input("yEnd:\n")
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
        print "processing " + dst + writePre + numStr + writePost
        for i in xrange(yBeg,yEnd+1):
            for j in xrange(xBeg,xEnd+1):
                yStr = "%d"%(i)
                xStr = "%d"%(j)
                filename = src + numStr + "\\" + readPre + numStr + "_" + xStr + "_" + yStr + readPost    
                subimg = cv2.imread(filename,cv2.CV_LOAD_IMAGE_UNCHANGED)
                if isReverse == 0:
                    img[(i-yBeg)*xWidth:(i+1-yBeg)*xWidth,(j-xBeg)*yWidth:(j+1-xBeg)*yWidth] = subimg
                if isReverse == 1:
                    subimg = subimg[:,::-1]
                    img[(i-yBeg)*xWidth:(i+1-yBeg)*xWidth,(j-xBeg)*yWidth:(j+1-xBeg)*yWidth] = subimg               
        cv2.imwrite(dst + writePre + numStr + writePost,img)
#         print dst + writePre + numStr + writePost


def autoTar(usedArray,imPre,imPost,dstFile):
    readPre =  imPre     # string
    readPost = imPost     # string
    dstPath = dstFile        # string    
    print dstPath
    for i in range(len(usedArray)):
        numStr = "%05d"%(usedArray[i])
        filename = readPre+numStr+readPost
        print filename
        if os.path.exists(filename):
            print "taring " + filename
            tar= tarfile.open(filename)
            names = tar.getnames()
            for name in names:
                tar.extract(name,path=dstPath)
            tar.close()        
        else:
            pass

def project(usedArray,s,d,n):
    src = s
    dst = d
    readPre = "test_"
    readPost = "_mon.tif"
    writePre = "test_"
    wirtePost = "_pro.tif"
    blockNum = n
    sA = usedArray    
    for j in range(0,len(sA), blockNum):
        s = j
        e = j + blockNum - 1    
        if e > len(sA)-1:
            e = len(sA)-1
        print "process begin: %05d  end : %05d"%(sA[s], sA[e])
        sS = "%05d"%(sA[s])
        eS = "%05d"%(sA[e])
        for i in range(s, e+1):
            n = sA[i]
            numStr = "%05d"%(n)
            filename = src + readPre+numStr+readPost
            if i == s:
                img1 = cv2.imread(filename,cv2.CV_LOAD_IMAGE_UNCHANGED)
                img3 = np.zeros(img1.shape,np.uint8)
            else:
                img1 = cv2.imread(filename,cv2.CV_LOAD_IMAGE_UNCHANGED)
            img3 = np.maximum(img1,img3)
        print dst+writePre+sS+"-"+eS+wirtePost
        cv2.imwrite(dst+writePre+sS+"-"+eS+wirtePost,img3)    