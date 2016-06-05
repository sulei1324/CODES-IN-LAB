from mpi4py import MPI
from cv2 import inRange
comm=MPI.COMM_WORLD
size =comm.Get_size()
rank = comm.Get_rank()
name = MPI.Get_processor_name()
group=comm.Get_group()
print name,": ", rank
print group