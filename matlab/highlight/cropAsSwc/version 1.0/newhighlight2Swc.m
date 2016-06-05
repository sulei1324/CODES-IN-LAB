% function newhighlight()


clear all;
clc;
tic;

width=5072;
height=7000;
zRange=[768,1867];
level=zRange(2)-zRange(1)+1;
imImf=[width,height,level];
src=('Y:\Public\mostgroup\data_us\MBA-GF13004_cut\LDA\12-16\12_16-files\axonNearCellSub\');
dst=('G:\sulei\I9\count\axonNearCell\');
pre='axonNearCellRaw';
suf='.tif';
R=8;
swc1=load('G:\sulei\I9\count\anc\axonNearCell.swc');
[lightArea1,maxCoord1,minCoord1]=getLightArea(swc1,R,imImf);
swc2=load('G:\sulei\I9\count\anc\axonNearCell.swc');
[lightArea2,maxCoord2,minCoord2]=getLightArea(swc2,R,imImf);
totalMaxCoord=max(maxCoord1,maxCoord2);
totalMinCoord=min(minCoord1,minCoord2);



% cropedWidth=1499;
% cropedHeight=1066;



cropedWidth=totalMaxCoord(1,1)-totalMinCoord(1,1)+1;
cropedHeight=totalMaxCoord(1,2)-totalMinCoord(1,2)+1;
inImage=zeros(cropedHeight,cropedWidth);
involvedZNum1=size(lightArea1,1);
involvedZNum2=size(lightArea2,1);

for i=1:involvedZNum1
    outImage=zeros(cropedHeight,cropedWidth);
    pointOfZ=lightArea{i,1};
    z=pointOfZ(1,3);
    zSerial=z-minCoord(1,3);
    inImage=imread([src pre num2str(zSerial,'%05d') suf]);
    pointNumOfZ=size(pointOfZ,1);
    disp(zSerial);
    for j=1:pointNumOfZ
        x=pointOfZ(j,1);
        y=pointOfZ(j,2);
        x=x-minCoord(1,1)+1;
        y=y-minCoord(1,2)+1;
        [x,y]=checkXY(x,y,cropedWidth,cropedHeight);
%         outImage(y,x)=255;
        outImage(y,x)=inImage(y,x);
    end
    
    outImage=uint8(outImage);
    size(outImage)
    imwrite(outImage,[dst num2str(i,'%05d') '.tif']);
    disp(i);
end




% toc;