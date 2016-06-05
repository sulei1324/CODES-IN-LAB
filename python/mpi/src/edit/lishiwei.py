import TDICorrector
import TDIShaper
def WriteShape(Lxy,numStr):
	f = open(readPre + numStr+".txt","w")
	for i in Lxy:
		f.write("%f %f\n"%(i[0], i[1]))
	f.close()
readPre = "/media/document/MyProject/TDI/"
readPost = ".jpg"
writePre = "/lustre/share/Public/mostgroup/TDI010_Preprocess/python/"
writePost = ".tif"
begNum = input("Please input begin num\n")
endNum = input("Please input end num\n")
Lxy = TDIShaper.ReadInitialShape('/home/zhouhang/TDI/lj/test_txt/test_03048.txt')
for z in xrange(begNum, endNum+1):
	numStr = "%05d"%(z)
	filename = readPre+numStr+readPost
	print "processing "+filename
	image = cv2.imread(readPre,cv2.CV_LOAD_IMAGE_UNCHANGED)
	LxyNew = TDIShaper.ShapeFit(img, Lxy)
    	Lx = TDIShaper.Smooth(LxyNew[:,0],1)
    	Ly = TDIShaper.Smooth(LxyNew[:,1],1)
    	Lxy = np.hstack((Lx.reshape(Lx.shape[0],1), Ly.reshape(Ly.shape[0],1)))
	WriteShape(Lxy, numStr)
	binImg = np.zeros(image.shape, np.uint8)
	ImageFillHole(Lxy, image, binImg)
	image1 = StripCorrect(binImg, image, 0.2)
	cv2.imwrite(writePre+numStr+writePost,image1)
