% function newhighlight()


clear all;
clc;
tic;

width=256;
height=873;
zRange=[0,186];
level=zRange(2)-zRange(1)+1;
imImf=[width,height,level];
src=('W:\lsu\TDI072\figure\3\all_cell\crop\3_highlight\b1\');
dst=('W:\lsu\TDI072\figure\3\all_cell\crop\3_highlight\h_b1\');
pre='3_7_b1';
suf='.tif';
R=8;
swc=load('W:\lsu\TDI072\figure\3\all_cell\crop\3_7_b1\real_local_3_branch1.swc');
[lightArea,maxCoord,minCoord]=getLightArea(swc,R,imImf);



% cropedWidth=1499;
% cropedHeight=1066;



cropedWidth=maxCoord(1,1)-minCoord(1,1);
cropedHeight=maxCoord(1,2)-minCoord(1,2);
inImage=zeros(cropedHeight,cropedWidth);
involvedZNum=size(lightArea,1);


for i=1:involvedZNum
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