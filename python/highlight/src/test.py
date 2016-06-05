__author__ = 'Su Lei'
import cv2 as cv
import numpy as np

# a = [[1, 0.36], [3, 0.16]]
# 
# def cmp(x, y):
#     if x[1] > y[1]:
#         return 1
#     else:
#         return -1
# 
# # cmp1 = lambda x, y: int(x[1] - y[1])
# a.sort(cmp)
# print a

# f = open('W:\\lsu\\TDI072\\1\\highlight\\test.txt', 'r')
# for i in f:
#     print i

def test(b):
    b.put(5, 100)
    test1(b)

def test1(c):
    c.put(4, 2000)


# m, n = test()
# print m, n
a = np.array(((2, 3, 4), (8, 5, 1)))
d = a
test(a)
print a.take(5), a.take(4)
print a, d

