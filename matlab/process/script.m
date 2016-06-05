clc;

clear all;

% I1=imread('cell.tif');
% I2=imread('cell_back.tif');
% I=I1-I2;
% I=uint8(I);
% imshow(I);




% a=[1,0,1;0,1,0;1,0,1];
% 
% a=logical(a);
% 
% a=sparse(a);
% 
% b=magic(3);
% 
% c=zeros(3,3);
% 
% b(a)=c(a);

% a=load('19.mat');
% b=[];
% b=a.v;
% m=size(b,1);
% c=zeros(32200,23400);
% for i=1:m
%     x=b(i,1);
%     y=b(i,2);
%     z=b(i,3);
%     c(y,x)=1;
% end
% 
% c=logical(c);
% c=sparse(c);


h=fspecial('gaussian',100,0.1);

I=imread('cell.tif');
imshow(I);
I=double(I);

% outImage=conv2(I,h);
I1=imfilter(I,h,'replicate');
I2=I-I1;


I2=uint8(I2);


figure,imshow(I2);

