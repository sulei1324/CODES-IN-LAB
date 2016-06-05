clc;
clear all;

rgb16 = '#96582a';
r = hex2dec(rgb16(2 : 3));
g = hex2dec(rgb16(4 : 5));
b = hex2dec(rgb16(6 : 7));
res = [r / 255, g / 255, b / 255];
disp(res);