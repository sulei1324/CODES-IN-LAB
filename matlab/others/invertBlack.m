clc;

clear all;

I1=imread('W:\lsu\movie\11-6movie\neutron\bouton\RGB-I2.bmp');

[m,n,l]=size(I1);

for i=1:m
    for j=1:n
        if((I1(i,j,1)==0)&&(I1(i,j,2)==0)&&(I1(i,j,3)==0))
%             disp(i);
%             disp(j);
            I1(i,j,1)=255;
            I1(i,j,2)=255;
            I1(i,j,3)=255;
        end
    end
end

imshow(I1);