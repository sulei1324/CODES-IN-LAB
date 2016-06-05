% function newhighlight()


clear all;
clc;
tic;

width=23712;
height=36400;
zRange=[14,8375];
level=zRange(2)-zRange(1)+1;
imImf=[width,height,level];
src=('Y:\Public\mostPreprocess\TDI048_red\montage\');
dst=('W:\lsu\TDI048\used\black_new\');
pre='test_';
suf='python.tif';
R=2;
swc=load('W:\lsu\TDI048\used\axons_used.swc');

xS=4500;
yS=14000;
cropedWidth=15600;
cropedHeight=13200; 
[lightArea,maxCoord,minCoord]=getLightArea(swc,R,imImf);
inImage=zeros(height,width);
outImage=zeros(cropedHeight,cropedWidth);
tmpImage=zeros(cropedHeight,cropedWidth,3);
involvedZNum=size(lightArea,1);


for i=1:involvedZNum
    tic;
    pointOfZ=lightArea{i,1};
    z=pointOfZ(1,3);
    zSerial=z+zRange(1)-1;
%     inImage=imread([src pre num2str(zSerial,'%05d') suf]);
    pointNumOfZ=size(pointOfZ,1);
    disp(['disposing ' src pre num2str(zSerial,'%05d') suf]);
    outImage(:,:)=zeros(cropedHeight,cropedWidth);
    outImage=uint8(outImage);
%     imwrite(outImage,[dst num2str(zSerial,'%05d') '_c.tif']);
%     disp(['done ' dst num2str(zSerial,'%05d') '_c.tif']);
    tmpImage=repmat(outImage,[1,1,3]);
    for j=1:pointNumOfZ
        x=pointOfZ(j,1)-xS+1;
        y=pointOfZ(j,2)-yS+1;
        z=pointOfZ(j,3);
%         outImage(y,x)=255;
        tmpImage(y,x,:)=[255,0,0];
    end
    tmpImage=uint8(tmpImage);
    imwrite(tmpImage,[dst num2str(zSerial,'%05d') '-b.tif']);    
    disp(['done ' dst num2str(zSerial,'%05d') '-b.tif']);
    toc;
end




toc;