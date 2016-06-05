__author__ = 'Su Lei'

import swc



width = 23760
height = 35000
zRange = [6,11900]
src = 'Y:\\Public\\mostPreprocess\\TDI072\\montage\\'
dst = '.\\test\\'
pre = 'test_'
post = '_mon.tif'

write_pre = 'test_'
write_post = '_highlight.tif'
outSwcNum = swc.readSwc('W:\\lsu\\TDI072\\1\\highlight\\branch1_used.swc')
doSub = True
swc.trimSwc(outSwcNum)
linesInSwc = swc.convert2line(outSwcNum)
insertedLines = swc.insertLines(linesInSwc, 5)
allPoints = swc.getAllCordinates(insertedLines, 10, width, height, zRange)
highlightArea = swc.getArea(allPoints)
pointsGroupedByZ = swc.groupByZ(allPoints, (highlightArea[2][0], highlightArea[2][1]))
swc.doHighlight(highlightArea, width, height, src, dst, pre, post, write_pre, write_post, pointsGroupedByZ, doSub)