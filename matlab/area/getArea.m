clc;
clear all;

src = 'W:\lsu\TDI072\contour-olfactory bulb\sl\crop\test\00052.tif';
image1 = imread(src);
area1 = size(find(image1 ~= 0), 1);
