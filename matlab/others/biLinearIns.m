clc;
clear all;

I=imread('E:\sulei\1.tif');

[m,n]=size(I);
temp=zeros(m,n);
for i=1:m
    for j=1:n
        [pUp,pDown,pLeft,pRight]=N4(i,j,m,n);
        temp(i,j)=I(pUp,j)*1/4+I(pDown,j)*1/4+I(i,pLeft)*1/4+I(i,pRight)*1/4;
    end
end

I=temp;
I=uint8(I);
imwrite(I,'E:\sulei\2.tif');
        