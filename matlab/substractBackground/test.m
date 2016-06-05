clc;
clear all;

i1 = imread('1_bg.tif');

i2 = imread('2.tif');

i3 = imread('5.tif');

z = i3 - i2;
