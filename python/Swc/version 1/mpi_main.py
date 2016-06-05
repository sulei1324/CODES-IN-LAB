# -*- coding: utf-8 -*-


#from mpi4py import MPI
#import sys
#import readMostd as rmd
#import readSwc as rs
#
#size = MPI.COMM_WORLD.Get_size()
#rank = MPI.COMM_WORLD.Get_rank()
##name = MPI.Get_processor_name()
#dst = "W:\\lsu\\TDI072\\figure\\4\\6\\b6\\"
#
#print rank
#swc = rs.Swc("W:\\lsu\\TDI072\\figure\\4\\6\\6jyaxon_6.swc", (0.3, 0.3, 1))
#z_start = swc.real_roi[2]
#whole_job_num = swc.real_roi[5]
#each_job_num = whole_job_num / size
#job_start_array = [0] * size
#job_end_array = [0] * size
#tmp_z_start = z_start
#for i in xrange(size):
#    job_start_array[i] = tmp_z_start
#    if (tmp_z_start + each_job_num - 1) > (z_start + whole_job_num - 1):
#        job_end_array[i] = z_start + whole_job_num - 1
#    else:
#        job_end_array[i] = tmp_z_start + each_job_num - 1
#    
#    tmp_z_start = job_end_array[i] + 1
#
#
#print job_start_array
#print job_end_array

import math

print int(math.ceil(10/float(3)))





