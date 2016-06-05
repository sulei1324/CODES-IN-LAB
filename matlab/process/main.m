clc;

clear all;

I=imread('raw_crop.tif');
I=double(I);
% I=magic(5);

[m,n]=size(I);

R=50;
L=R;
sigma=1;

mirroredI=mirrorBundary(I,R);

tmpI=chooseMax(mirroredI,R);

tmpI2=bilinearMax(tmpI,R);
% tmpI2=uint8(tmpI2);
g=gussian(2*L,sigma);

% [mg,ng]=size(g);


back=convWithG(tmpI2,g);

% outImage=tmpI3(mg:mg+m-1,ng:ng+n-1);


outImage=back-I;

for i=1:m
    for j=1:n
        if(outImage(i,j)>255)
            outImage(i,j)=255;
        end
        if(outImage(i,j)<0)
            outImage(i,j)=0;
        end
    end
end


outImage=uint8(outImage);
back=uint8(back);
imshow(back);
figure,imshow(outImage);


