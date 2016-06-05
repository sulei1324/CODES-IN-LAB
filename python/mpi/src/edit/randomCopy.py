import os,shutil
begNum = input("input beg num: \n")
endNum = input("input end num: \n")
readPre = "/lustre/share/Public/mostPreprocess/TDI036/montage/test_"
readPost = "python.tif"
writePre = "/lustre/share/Public/mostPreprocess/TDI036/ldaSrc/test_"

for i in xrange(begNum, endNum + 1):
	print "copying image %05d" %i
	fileName = readPre + "%05d"%i + readPost
	writeName = writePre + "%05d"%i + readPost
	shutil.copyfile(fileName, writeName)
