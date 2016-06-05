import os,sys,getopt
import string
import tarfile
opts,args = getopt.getopt(sys.argv[1:],"",["readpre=","dstpath=","begnum=","endnum="])
for name,value in opts:
	if name in ("--readpre"):
		readPre = value
	if name in ("--dstpath"):
		dstPath = value
	if name in ("--begnum"):
		begNum = int(value)
	if name in ("--endnum"):
		endNum = int(value)
print "readpre ",readPre
print "dstpath ", dstPath
print begNum, "  ",endNum
#exit()
#readPre = "/lustre/share/RawData/TDI061/R/"
#readPost = input("Please input readPost\n")
readPost = ".tar"
#dstPath = "/lustre/share/Public/mostPreprocess/TDI061/Red/src/"#input("Please input dest path\n")
#begNum = input("Please input begNum\n")
#endNum = input("Please input endNum\n")
for i in xrange(begNum, endNum+1):
        numStr = "%05d"%(i)
        filename = readPre+numStr+readPost
        if os.path.exists(filename):
                print filename+" exists"
        else:
                print filename+" not exists"
                exit(0)
for i in xrange(begNum, endNum+1):
        numStr = "%05d"%(i)
        filename = readPre+numStr+readPost
        tar= tarfile.open(filename)
        print "tar "+filename
        names = tar.getnames()
        for name in names:
                #print name
                tar.extract(name,path=dstPath)
        tar.close()
