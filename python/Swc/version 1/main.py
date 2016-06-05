# -*- coding: utf-8 -*-

import readMostd as rmd
import readSwc as rs

dst = "W:\\lsu\\TDI072\\figure\\all\\1\\"
swc = rs.Swc(r"W:\lsu\TDI11302020\sl\swc\raw\b10.swc", (0.3, 0.3, 1))
#print swc.real_roi
print swc.fiber_length
#print swc.max_level
real_roi = swc.real_roi
print real_roi
#swc_roi = rmd.Roi(real_roi, r'W:\lsu\TDI11302020\TDI11302020_mostd_z.mostd')
#swc_roi.outputImages(dst, False)
#swc.trans_to_local_swc(swc.real_roi, True, dst)
###swc.trans_to_local_real_swc(swc.real_roi, dst)     