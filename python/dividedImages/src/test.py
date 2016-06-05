import tifffile as tf
import numpy as np


# 
# import os
# 
# # os.mkdir('G:\\sulei\\workplace\\fmostd\\src\\tttt')
# a = tifffile.imread('Stack.tif')
# print a.dtype, a.shape


# a = np.array([[1, 2], [4, 5]])
# d = np.array([[[1, 2]]])
# b = np.array([[[6, 5]]])
# c = np.concatenate((d, b), axis=0)
# print c[1, 0, 1], c[1, 0, 0]
# d = np.array([[[5, 6], [5, 2]], [[4, 5], [8, 1]]])
# a = np.array([1, 2, 3, 4])
# b = a.reshape((2, 2))
# c = b.reshape((1, 2, 2))
# print np.concatenate((d, c))

a = tf.imread('00001-0.tif')
b = tf.imread('00002-0.tif')
print a.shape, b.shape
a = a.reshape((1, a.shape[0], a.shape[1]))
b = b.reshape((1, b.shape[0], b.shape[1]))
print a.shape, b.shape
c = np.concatenate((a, b))
print c.shape
tf.imsave('12.tif', c)