# -*- coding: utf-8 -*-

import readSwc as rs
import funs
import readMostd as rm
#import vtk
#import libtiff as lt


swc_src = '../res/axon_test.swc'
mostd_src = '../res/TDI072-test.mostd'
dst = 'G:\\sulei\\workplace\\Swc\\result\\'
image_resolution = (0.3, 0.3, 1)
block_width = 512
block_height = 512
block_depth = 256



swc = rs.Swc(swc_src, image_resolution)

line = swc.lines[0]
points = line.points
i = 0
for s, e in zip(xrange(0, len(points), 10), xrange(10, len(points), 10)):
    used_10_points = points[s : e + 1]
    used_center = funs.get_center(used_10_points)
    block_section = funs.get_section(used_center, block_width, block_height, block_depth, image_resolution)
    used_images = rm.Roi(block_section, mostd_src).getImages()
    funs.save_vtk_image(used_images, dst, i)
    print i
    i += 1
    
    
    



