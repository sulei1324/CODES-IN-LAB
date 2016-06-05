# -*- coding: utf-8 -*-

import readMostd as rmd
import readSwc as rs


swc = rs.Swc(".\\res\\dendrite.swc", (0.3, 0.3, 1))
swc.displayInVtk()

