% function newhighlight()


clear all;
clc;
tic;

width=4000;
height=6000;
zRange=[10000,11846];
level=zRange(2)-zRange(1)+1;
imImf=[width,height,level];
src=('Y:\Public\mostgroup\data_us\MBA-GF13004_100-6100\I2_files\1_sub\');
dst=('W:\yjia\I\axon\');
pre='';
suf='.tif';
R=8;
swc=load('Y:\Public\mostgroup\data_us\MBA-GF13004_100-6100\I2_files\I1-T_I2-C\I2_axon.swc');


outImage=zeros(height,width);
inImage=zeros(height,width);
lightArea=getLightArea(swc,R,imImf);
involvedZNum=size(lightArea,1);
newZRange=[];

for i=1:involvedZNum
    outImage=zeros(height,width);
    pointOfZ=lightArea{i,1};
    z=pointOfZ(1,3);
    zSerial=z+zRange(1)-1;
    newZRange=[newZRange;zSerial];
    inImage=imread([src pre num2str(zSerial,'%05d') suf]);
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
    imwrite(outImage,[dst num2str(zSerial,'%05d') '.tif']);
    disp(i);
end


maxNZ=max(newZRange);
minNZ=min(newZRange);
outImage=zeros(height,width);
for i=zRange(1):zRange(2)
    if((i>=minNZ)&&(i<=maxNZ))
        continue;
    else
        imwrite(outImage,[dst num2str(i,'%05d') '.tif']);
    end
end



toc;