clc;
clear all;

z = 476;
dst = 'W:\lsu\TDI11302020\red\test\reversed\';

for i = z : -1 : 1
    a = imread('W:\lsu\TDI11302020\red\test\10u.tif', i);
    imwrite(a, [dst num2str((476 - i), '%05d') '.tif']);
end