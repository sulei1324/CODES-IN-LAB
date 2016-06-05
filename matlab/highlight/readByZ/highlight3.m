% function newhighlight()


clear all;
clc;
tic;

width=1001;
height=601;
zRange=[0,400];
xS = 10800;
yS = 23800;
zS = 4600;
level=zRange(2)-zRange(1)+1;
imImf=[width,height,level, xS, yS, zS];
src=('W:\lsu\TDI072\1\axon\branch3\3-1sub\');
dst=('W:\lsu\TDI072\1\axon\branch3\3-1hl\');
pre='3-1block-';
suf='.tif';
R=10;
swc=load('W:\lsu\TDI072\1\axon\branch3\cross.swc');

    
outImage=zeros(height,width);
inImage=zeros(height,width);
lightArea=getLightArea(swc,R,imImf);
involvedZNum=size(lightArea,1);

for i=1:involvedZNum
    outImage=zeros(height,width);
    pointOfZ=lightArea{i,1};
    if(size(pointOfZ, 1) == 0)
        continue;
    end
    z=pointOfZ(1,3);
    zSerial=z;
    inImage=imread([src pre num2str(zSerial,'%04d') suf]);
    pointNumOfZ=size(pointOfZ,1);
    disp(zSerial);
    for j=1:pointNumOfZ
        x=pointOfZ(j,1);
        y=pointOfZ(j,2);
        z=pointOfZ(j,3);
        if(x == 0 || y == 0)
            continue;
        end
%         outImage(y,x)=255;
        outImage(y,x)=inImage(y,x);
    end
    outImage=uint8(outImage);
    imwrite(outImage,[dst num2str(i,'%05d') '.tif']);
    disp(i);
end




toc;