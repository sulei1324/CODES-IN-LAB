import string
import findLostFile as flf
import allocateNum as aN
import AutoTar as at
import mpi4py
from mpi4py import MPI

comm = MPI.COMM_WORLD
rank = comm.Get_rank()
mpiSize = comm.Get_size()
name = MPI.Get_processor_name()


if rank == 0:
    # begNum = input("Please input begNum\n")        # number
    # endNum =  input("Please input endNum\n")        # number
    # readPre = raw_input("Please input readPre.\n")        # string
    # readPost = raw_input("Please input readPost\n")      # string
    # srcPath = raw_input("Please input srcPath\n") 
    # dstPath = raw_input("Please input dest path\n")        # string
    # mpiSize = input('How many processes do you want to open: ')
    # nodesName = ranw_input('Please input the node name you will use: ')
    begNum = 900      # number
    endNum =  5000    # number
    readPre = ''       # string
    readPost = '.tar'      # string
    srcPath = 'G:\\sulei\\13004\\test\\'        # string
    dstPath = 'G:\\sulei\\13004\\test\\'
    terminateFlag = None
#    flf.printLostFile(begNum, endNum, srcPath, readPre, readPost)
    eA = flf.getAvailSerial(begNum, endNum, srcPath, readPre, readPost)
    if eA == None:
        print "There is no file to dispose."
        terminateFlag = 1
    else:
        uA = aN.alloNum(mpiSize, eA)  
      
        for i in range(len(uA)):
            if i == 0:
                sA = uA[i]
            else:
                comm.send(uA[i],dest=i,tag=77)
      
else:
    sA = None
    readPre = None
    readPost = None
    srcPath = None
    dstPath = None
    terminateFlag = None

terminateFlag = comm.bcast(terminateFlag,root=0)
print rank,terminateFlag
if terminateFlag == 1:
    print "the end: ",rank
    exit()

if rank !=0:
    sA = comm.recv(source=0,tag=77)
    
print sA,rank    
readPre = comm.bcast(readPre,root=0)
readPost = comm.bcast(readPost,root=0)
srcPath = comm.bcast(srcPath,root=0)
dstPath = comm.bcast(dstPath,root=0)
 
if sA == []:
    print name+" is not working!"
    exit()     
  
  
filePre = srcPath + readPre
at.autoTar(sA, filePre, readPost, dstPath)
      
    

        
        
    

                
                
       
    
       