clc;
clear all;

a = imread('2.tif');

b = edge(a);
imshow(b);