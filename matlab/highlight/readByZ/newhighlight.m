% function newhighlight()


clear all;
clc;
tic;

width=1636;
height=1340;
zRange=[0,478];
level=zRange(2)-zRange(1)+1;
imImf=[width,height,level];
src=('W:\lsu\TDI072\figure\all\1\');
dst=('W:\lsu\TDI072\figure\all\1h\');
pre='';
suf='.tif';
R=10;
swc=load('W:\lsu\TDI072\figure\all\local_b10.swc');


outImage=zeros(height,width);
inImage=zeros(height,width);
lightArea=getLightArea(swc,R,imImf);
involvedZNum=size(lightArea,1);


for i=1:involvedZNum
    outImage=zeros(height,width);
    pointOfZ=lightArea{i,1};
    z=pointOfZ(1,3);
    zSerial=z+zRange(1)-1;
    inImage=imread([src pre num2str(zSerial,'%05d') suf]);
    pointNumOfZ=size(pointOfZ,1);
    disp(zSerial);
    for j=1:pointNumOfZ
        x=pointOfZ(j,1)+50;
        y=pointOfZ(j,2)+50;
        z=pointOfZ(j,3);
%         outImage(y,x)=255;
        outImage(y,x)=inImage(y,x);
    end
    outImage=uint8(outImage);
    imwrite(outImage,[dst num2str(i,'%05d') '.tif']);
    disp(i);
end




toc;