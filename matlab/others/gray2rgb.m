clear all;
clc;

I=imread('W:\lsu\matlab\test_dst\gray2rgb\1.tif');
J=imread('W:\lsu\matlab\test_dst\gray2rgb\2.tif');

A=repmat(I,1,1,3);
B=double(A);
A(150,150,:)
figure,imshow(J);
for i=100:150
    for j=100:150
        A(i,j,:)=[0 255 60];
    end
end
imshow(A);