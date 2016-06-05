import string
import mpi4py
from mpi4py import MPI
import sys
import funLib as flib

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
    begNum = int(sys.argv[2])
    endNum = int(sys.argv[3])
    samNum = sys.argv[1]
    srcRoot = "G:\\sulei\\workplace\\mpi\\src\\test\\rawdata\\"
    dstRoot = "G:\\sulei\\workplace\\mpi\\src\\test\\result\\"
    print begNum,endNum,samNum,rank
    tarPre = ''       # string
    tarPost = '.tar'      # string
    tarSrc = srcRoot + samNum + "\\"       # string
    tarDst = dstRoot + samNum + "\\" + "src\\"
    monSrc = tarDst
    monDst = dstRoot + samNum + "\\"  + "montage\\"
    terminateFlag = None
#    flf.printLostFile(begNum, endNum, srcPath, readPre, readPost)
    eA = flib.getAvailSerial(begNum, endNum, tarSrc, tarPre, tarPost)
    if eA == None:
        print "There is no file to dispose."
        terminateFlag = 1
    else:
        uA = flib.alloNum(mpiSize, eA)  
       
        for i in range(len(uA)):
            if i == 0:
                sA = uA[i]
            else:
                comm.send(uA[i],dest=i,tag=77)
       
else:
    sA = None
    tarPre = None
    tarPost = None
    tarSrc = None
    tarDst = None
    monSrc = None
    monDst = None
    terminateFlag = None
 
terminateFlag = comm.bcast(terminateFlag,root=0)
print rank,terminateFlag
if terminateFlag == 1:
    print "the end: ",rank
    exit()
 
if rank !=0:
    sA = comm.recv(source=0,tag=77)
     
print sA,rank    
tarPre = comm.bcast(tarPre,root=0)
tarPost = comm.bcast(tarPost,root=0)
tarSrc = comm.bcast(tarSrc,root=0)
tarDst = comm.bcast(tarDst,root=0)
monSrc = comm.bcast(monSrc,root=0)
monDst = comm.bcast(monDst,root=0)
  
if sA == []:
    print  "rank " + str(rank) + " in " + name +" is not working!"
    exit()     
   

flib.autoTar(sA, tarSrc + tarPre, tarPost, tarDst)

flib.montage(sA,monSrc,monDst)





#       
    

        
        
    

                
                
       
    
       