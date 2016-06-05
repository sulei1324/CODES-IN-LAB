clear all;
clc;

f=fopen('1.txt');
A=fread(f);
disp(A);
fclose(f);
B=char(A);
