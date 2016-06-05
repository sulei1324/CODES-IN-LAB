# -*- coding: utf-8 -*-

import libtiff as lt

import numpy as np

a = np.zeros((4, 10, 10), dtype=np.uint8)
a[2, 5:8, 3:6] = np.ones((3, 3), dtype=np.uint8) * 255

t = lt.TIFF3D.open('3d.tif', 'w')
t.write_image(a);
t.close()



g = lt.TIFF3D.open('13_0_0.tif', 'r')
print g.NumberOfStrips()
#g.SetDirectory(2)
#b = np.zeros((1, 100), np.uint8)
#print g.ReadEncodedStrip(0, b.ctypes.data, 100), b
#print b.ctypes

    




