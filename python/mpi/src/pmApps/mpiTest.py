from mpi4py import MPI
import sys

comn = MPI.COMM_WORLD
size = MPI.COMM_WORLD.Get_size()
rank = MPI.COMM_WORLD.Get_rank()
name = MPI.Get_processor_name()
print name,": ", rank, 'of', size

if rank == 0:
    print "hehe"
    comn.send("aaa", dest=1)
    
if rank == 1:
    d = comn.recv(source=0)
    print d