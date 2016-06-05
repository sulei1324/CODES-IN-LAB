clear all;
clc;
tic;

width=23400;
height=32200;
zRange=[18,7334];
level=zRange(2)-zRange(1)+1;
imImf=[width,height,level];
src=('W:\lsu\anlysis\raw\');
dst=('W:\lsu\anlysis\I10\X1\');
suf='.swc';
R=10;
swc=load('W:\lsu\anlysis\raw\I9_x1.swc');

[lightArea,maxCoord,minCoord]=getLightArea(swc,R,imImf);
involvedZNum=size(lightArea,1);

