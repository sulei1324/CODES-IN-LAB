import cv,cv2,os,string,shutil
import numpy as np
readPre="/lustre/share/Public/mostPreprocess/TDI037/src/"
readMid1="test_"
readMid2=".jpg"
readPost=".jpg"
writePre="/lustre/share/Public/mostPreprocess/TDI037/montage/"
writePost=".tif"
cacheDirName="TDI037_src/"
tmpDir="/dev/shm/"+cacheDirName
os.mkdir(tmpDir)
begNum=input("Please input begin num\n")
endNum=input("Please input end num\n")
xBeg=input("xBeg:\n")
xEnd=input("xEnd:\n")
yBeg=input("yBeg:\n")
yEnd=input("yEnd:\n")
for i in xrange(begNum, endNum+1):
        numStr = "%05d"%(i)
        filename = readPre+numStr+"/"
        if os.path.exists(filename):
                print filename+" exists"
        else:
                print filename+" not exists"
                exit(0)
z=begNum
numStr="%05d"%(z)
xStr="%d"%(xBeg)
yStr="%d"%(yBeg)
filename=readPre+numStr+"/"+"test__"+numStr+"_"+xStr+"_"+yStr+readPost
cacheName=tmpDir+"test_"+numStr+"_"+xStr+"_"+yStr+readPost
shutil.copyfile(filename,cacheName)
subimg=cv2.imread(cacheName,cv2.CV_LOAD_IMAGE_UNCHANGED)
xWidth=subimg.shape[0]
yWidth=subimg.shape[1]
barWidth=129
img=np.zeros((subimg.shape[0]*(yEnd-yBeg+1)-barWidth,subimg.shape[1]*(xEnd-xBeg+1)),np.uint8)
img1=np.zeros((subimg.shape[0]*(yEnd-yBeg+1),subimg.shape[1]),np.uint8)
tmp=np.zeros((subimg.shape[0]*(yEnd-yBeg+1),subimg.shape[1]),np.uint8)
os.remove(cacheName)
#print img.shape
for z in xrange(begNum, endNum+1):
	numStr="%05d"%(z)
	print "processing "+"test_"+numStr+"python.tif"
	for i in xrange(xBeg,xEnd+1):
		for j in xrange(yBeg,yEnd+1):
			xStr="%d"%(i)
			yStr="%d"%(j)
			filename=readPre+numStr+"/"+"test__"+numStr+"_"+xStr+"_"+yStr+readPost
			cacheName=tmpDir+"test_"+numStr+"_"+xStr+"_"+yStr+readPost
			shutil.copyfile(filename,cacheName)
			subimg=cv2.imread(cacheName,cv2.CV_LOAD_IMAGE_UNCHANGED)
			os.remove(cacheName)
			subimg=subimg[:,::-1]
			img1[(j-yBeg)*xWidth:(j+1-yBeg)*xWidth,:]=subimg
		if ((i-xBeg)%2==1):
			tmp=img1[::-1,:]
			img[:,(i-xBeg)*yWidth:(i+1-xBeg)*yWidth]=tmp[0:subimg.shape[0]*(yEnd-yBeg+1)-barWidth,:]
		else:
			img[:,(i-xBeg)*yWidth:(i+1-xBeg)*yWidth]=img1[barWidth:subimg.shape[0]*(yEnd-yBeg+1),:]		
	cv2.imwrite(tmpDir+"test_"+numStr+"python.tif",img)
	shutil.move(tmpDir+"test_"+numStr+"python.tif",writePre+"test_"+numStr+"python.tif")
shutil.rmtree(tmpDir)
