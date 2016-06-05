def pingpong(comm,whoPass,data):
    rank=comm.Get_rank()
    if(whoPass):
        if rank==0:
            passData=data
            comm.send(passData,dest=1)
        else:
            passData=None
            passData=comm.recv(source=0)
            passData=passData+1
            print passData
    else:
        if rank==0:
            passData=None
            passData=comm.recv(source=1)
            passData=passData+1
            print passData            
        else:
            passData=data
            comm.send(passData,dest=0)


import mpi4py as mpi
from mpi4py import MPI
  
comm=MPI.COMM_WORLD
data=1;
for i in range(10):
    whoPass=i%2
    pingpong(comm,whoPass,i)
    
    


    
    
            



# rank=comm.Get_rank()
# index=0


# if rank==0:
#     data=1
#     recFlagF=0
#     if(recFlagF):
#     	data=comm.recv(source=1)
#     	data=data+1
#     	print data	
#     else:
#     	comm.send(data,dest=1)		
#     	recFlagF=1
# else:
#     data=None
#     recFlagS=1
#     if(recFlagS):
#     	data=comm.recv(source=0)
#     	data=data+1
#     	print data	
#     else:
#     	comm.send(data,dest=0)
#     	recFlagS=1
   
# if rank==0:
#     data=1
#     comm.send(data,dest=1) 
#     data=comm.recv(source=1)
#     data=data+1
#     print data        
# else:
#     data=None
#     data=comm.recv(source=1)
#     data=data+1
#     print data  
#     comm.send(data,dest=1) 
#    
