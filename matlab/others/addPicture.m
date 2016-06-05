clc;
clear all;

width=5072;
height=7000;
p1Info=[1333,4357,2212,4780];
p2Info=[1472,3592,3297,5143];
p1=imread('G:\sulei\I9\count\figure\cell\MAX_axonNearCell.tif');
p2=imread('G:\sulei\I9\count\figure\cell\MAX_I9.tif');
p1Width=p1Info(1,2)-p1Info(1,1);
p1Height=p1Info(1,4)-p1Info(1,3);


outImage1=zeros(height,width);
outImage1=uint8(outImage1);
outImage2=zeros(height,width);
outImage2=uint8(outImage2);



outImage1(p1Info(1,3):p1Info(1,4)-1,p1Info(1,1):p1Info(1,2)-1)=p1(:,:);
outImage2(p2Info(1,3):p2Info(1,4)-1,p2Info(1,1):p2Info(1,2)-1)=p2(:,:);


outImage=max(outImage1,outImage2);




imwrite(outImage,'./1.tif');