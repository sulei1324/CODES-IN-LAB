import os

# os.system('export LD_LIBRARY_PATH=/opt/gcc482/lib64')

os.system('/usr/mpi/gcc/openmpi-1.4.3/bin/mpirun -np 4 -hostfile ./hostfile  python ./mpiTest.py')