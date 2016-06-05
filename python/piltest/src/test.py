import numpy

a = numpy.array([[1,2,3],[4,5,6]])
b = numpy.array([[1,2,2],[7,1,4]])
c= numpy.zeros((4,3), numpy.uint8)
print numpy.transpose(c, (3, 4))
