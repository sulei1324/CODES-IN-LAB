clc;

clear all;

f=fopen('Y:\Public\mostzhangyalun\sulei\matlab\test\1.tif');

a=fread(f,'uint8');

fclose(f);