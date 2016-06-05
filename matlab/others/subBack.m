% function [outImage]=subBack(inImage)

clc;
clear all;
k=50;

sigma=1;

H=zeros(2*k+1,2*k+1);

a=2*pi*(sigma^2);
b=2*(sigma^2);

for i=1:2*k+1
    c=(i-k-1)^2;
    for j=2:2*k+1
        d=(j-k-1)^2;
        f=-(c+d)/b;
        H(i,j)=a*exp(f);
    end
end
Hsum=sum(sum(H));
H=H/Hsum;
I=imread('D:\sulei\MAX_Stack_4401-4800.tif');
R=50;
mr=round(R/2);
ml=round(R/2);
a=zeros(R,R);
a(mr,ml)=1;
% I=imresize(I,0.5);
% imwrite(I,'E:\sulei\MAX_54-s.tif');
I=double(I);


B=conv2(I,H,'same');

% B=conv(I,H);
% I=randn([9,9]);
% fun = @(x) H*x;
% 
% tic;
% B=blkproc(I,[7,7],fun);
% toc;

B=uint8(B);

imwrite(B,'D:\sulei\3.tif');