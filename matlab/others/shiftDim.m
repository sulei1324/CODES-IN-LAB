clc;

clear all;

cd Y:\Public\mostzhangyalun\sulei\matlab\test\zProjectTest;

a=imread('3-7_crop_resize.tif');

b=shiftdim(a,3);

imshow(a);

figure,imshow(b);

