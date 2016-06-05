import os
import string
import tarfile

def autoTar(usedArray,imPre,imPost,dstFile):
	readPre =  imPre     # string
	readPost = imPost     # string
	dstPath = dstFile		# string	
		
	for i in range(len(usedArray)):
		numStr = "%05d"%(usedArray[i])
		filename = readPre+numStr+readPost
		if os.path.exists(filename):
			tar= tarfile.open(filename)
			names = tar.getnames()
			for name in names:
				tar.extract(name,path=dstPath)
			tar.close()		
		else:
			pass









	
		

# for i in xrange(begNum, endNum+1):
# 	numStr = "%05d"%(i)
# 	filename = readPre+numStr+readPost
# 	tar= tarfile.open(filename)
# 	print "tar "+filename
# 	names = tar.getnames()
# 	for name in names:
# 		#print name
# 		tar.extract(name,path=dstPath)
# 	tar.close()

