%trace without cross analysization
str = '160_1.tif';
%read image 160_1.tif
z = 60;
origImg = zeros(135/2,161/2,60);
 for i = 1 :  z %128
   origImg(:,:,i) = (double(imread('160_1.tif',i)));%uint8
 end
 for i = 1 : z
    tmpImg(:,:,i) = origImg(:,:,i)';
 end
 origImg = tmpImg;