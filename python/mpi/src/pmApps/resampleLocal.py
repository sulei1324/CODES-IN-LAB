import cv2,os,string
readPre ="/lustre/share/Public/mostgroup/TDI030_Preprocess/Montage/test_" 
readPost = "python.tif"
writePre="/lustre/share/Public/mostgroup/TDI030_Preprocess/Montage/resample-2X2X2um/test_"
writePost="python.tif"
begNum = 17
endNum = 3587
newX = 3464
newY = 5249
thick = 10
for i in xrange(begNum, endNum + 1, thick):
	numStr = "%05d"%(i)
	print readPre+numStr+readPost
	origImg = cv2.imread(readPre+numStr+readPost,cv2.CV_LOAD_IMAGE_UNCHANGED)
	newImg = cv2.resize(origImg, (newX,newY))	
	cv2.imwrite(writePre+numStr+writePost,newImg)

