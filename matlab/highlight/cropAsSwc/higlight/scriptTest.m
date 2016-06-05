clear all;
clc;
tic;

width=23400;
height=32200;
zRange=[101,6100];
level=zRange(2)-zRange(1)+1;
imImf=[width,height,level];
src=('Y:\Archive\MBA-GF13004_preprocess\Src\100_6100\');
dst=('Y:\Public\mostzhangyalun\sulei\matlab\test_dst\highlightTest\30\');
pre='test_';
suf='.tif';
R=8;
swc=load('H:\sulei\I4.swc');


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
        x=pointOfZ(j,1);
        y=pointOfZ(j,2);
        z=pointOfZ(j,3);
        outImage(y,x)=inImage(y,x);
    end
    outImage=uint8(outImage);
    imwrite(outImage,[dst num2str(i,'%05d') '.tif']);
    disp(i);
end




toc;


%   Elapsed time is 180819.715168 seconds. 2369