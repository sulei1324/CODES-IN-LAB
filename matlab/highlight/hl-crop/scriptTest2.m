clear all;
clc;
tic;

width=23400;
height=32200;
zRange=[101,6100];
level=zRange(2)-zRange(1)+1;
imImf=[width,height,level];
src=('Y:\Archive\MBA-GF13004_preprocess\Src\100_6100\');
dst=('Y:\Public\mostzhangyalun\sulei\matlab\test_dst\highlightTest\29\');
pre='test_';
suf='.tif';
R=8;
swc=load('H:\sulei\I4.swc');


outImage=zeros(height,width);
inImage=zeros(height,width);
lightArea=getLightArea(swc,R,imImf);
involvedZNum=size(lightArea,1);