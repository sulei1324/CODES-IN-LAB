% function newhighlight()


clear all;
clc;
tic;

width=4000;
height=6600;
zRange=[0000,1846];
level=zRange(2)-zRange(1)+1;
imImf=[width,height,level];
src=('Y:\Public\mostgroup\data_us\MBA-GF13004_100-6100\I2_files\1_sub\');
dst=('G:\sulei\I2\I2-axon\');
pre='1';
suf='.tif';
R=10;
swc=load('Y:\Public\mostgroup\data_us\MBA-GF13004_100-6100\I2_files\I1-T_I2-C\I2_axon.swc');


outImage=zeros(height,width);
inImage=zeros(height,width);
lightArea=getLightArea(swc,R,imImf);
involvedZNum=size(lightArea,1);


for i=1:involvedZNum
    outImage=zeros(height,width);
    pointOfZ=lightArea{i,1};
    z=pointOfZ(1,3);
    zSerial=z+zRange(1)-1;
    inImage=imread([src pre num2str(zSerial,'%04d') suf]);
    pointNumOfZ=size(pointOfZ,1);
    disp(zSerial);
    for j=1:pointNumOfZ
        x=pointOfZ(j,1);
        y=pointOfZ(j,2);
        z=pointOfZ(j,3);
%         outImage(y,x)=255;
        outImage(y,x)=inImage(y,x);
    end
    outImage=uint8(outImage);
    imwrite(outImage,[dst num2str(i,'%05d') '.tif']);
    disp(i);
end




toc;