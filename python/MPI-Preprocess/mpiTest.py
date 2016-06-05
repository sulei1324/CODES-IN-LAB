from mpi4py import MPI
import sys
size = MPI.COMM_WORLD.Get_size()
rank = MPI.COMM_WORLD.Get_rank()
name = MPI.Get_processor_name()
print name,": ", rank
#fp = open('./%s'%name, 'w')
import cv2
#fp.write('I am %s'%name);
#fp.close()
