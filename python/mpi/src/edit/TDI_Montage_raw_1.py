import cv,cv2,os,string,shutil
import numpy as np
readPre="/lustre/share/Public/mostPreprocess/TDI048_green/src/"
readMid1="test_G__"
readMid2=".jpg"
readPost=".jpg"
writePre="/lustre/share/Public/mostPreprocess/TDI048_green/montage/"
writePost=".tif"
cacheDirName="TDI048_green/"
tmpDir="/dev/shm/"+cacheDirName
#os.mkdir(tmpDir)
begNum=input("Please input begin num\n")
endNum=input("Please input end num\n")
xBeg=input("xBeg:\n")
xEnd=input("xEnd:\n")
yBeg=input("yBeg:\n")
yEnd=input("yEnd:\n")
isReverse=input("is reverse?1:0\n")
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
filename=readPre+numStr+"/"+"test_G__"+numStr+"_"+xStr+"_"+yStr+readPost
cacheName=tmpDir+"test_G__"+numStr+"_"+xStr+"_"+yStr+readPost
#shutil.copyfile(filename,cacheName)
#subimg=cv2.imread(cacheName,cv2.CV_LOAD_IMAGE_UNCHANGED)
subimg=cv2.imread(filename,cv2.CV_LOAD_IMAGE_UNCHANGED)
xWidth=subimg.shape[0]
yWidth=subimg.shape[1]
img=np.zeros((subimg.shape[0]*(yEnd-yBeg+1),subimg.shape[1]*(xEnd-xBeg+1)),np.uint8)
#os.remove(cacheName)
#print img.shape
for z in xrange(begNum, endNum+1):
	numStr="%05d"%(z)
	print "processing "+"test_G__"+numStr+"python.tif"
	for i in xrange(yBeg,yEnd+1):
		for j in xrange(xBeg,xEnd+1):
			yStr="%d"%(i)
			xStr="%d"%(j)
			filename=readPre+numStr+"/"+"test_G__"+numStr+"_"+xStr+"_"+yStr+readPost
			#cacheName=tmpDir+"test_G__"+numStr+"_"+xStr+"_"+yStr+readPost
			#shutil.copyfile(filename,cacheName)
			#subimg=cv2.imread(cacheName,cv2.CV_LOAD_IMAGE_UNCHANGED)
			subimg=cv2.imread(filename,cv2.CV_LOAD_IMAGE_UNCHANGED)
			#os.remove(cacheName)
			if isReverse==0:
				img[(i-yBeg)*xWidth:(i+1-yBeg)*xWidth,(j-xBeg)*yWidth:(j+1-xBeg)*yWidth]=subimg
			if isReverse==1:
				subimg=subimg[:,::-1]
				img[(i-yBeg)*xWidth:(i+1-yBeg)*xWidth,(j-xBeg)*yWidth:(j+1-xBeg)*yWidth]=subimg
	#cv2.imwrite(tmpDir+"test_"+numStr+"python.tif",img)
	cv2.imwrite(writePre+"test_"+numStr+"python.tif",img)
	#shutil.move(tmpDir+"test_"+numStr+"python.tif",writePre+"test_"+numStr+"python.tif")
#shutil.rmtree(tmpDir)
