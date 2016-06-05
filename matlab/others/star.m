clc;
clear all;

width=23400;
height=32200;

swc=load('W:\lsu\anlysis\raw\c\I9_x1_c.swc');
x=swc(:,3)*10/3;
y=swc(:,4)*10/3;
scatter(y,x);
axis([0,height,0,width]);