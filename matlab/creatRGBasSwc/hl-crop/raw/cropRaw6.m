% % function newhighlight()
% 
% 
clear all;
clc;
tic;

width=23400;
height=32200;
zRange=[101,6100];
level=zRange(2)-zRange(1)+1;
imImf=[width,height,level];
src=('Y:\Archive\MBA-GF13004_preprocess\Src\100_6100\');
dst=('W:\lsu\allLong\tmp\I8_cell2\');
pre='test_';
suf='.tif';
R=10;
swc=load('W:\lsu\allLong\tmp\I8_cell2.swc');
marginA=50;
% swc1=load('Z:\jli\YFP12002_manualTrace\4101_4500_lijing\4101_4500-bright2_manual.swc');
% swc2=load('Z:\jli\YFP12002_manualTrace\4101_4500_lijing\4101_4500-bright5_manual.swc');
% swc = MergeTwoSwc(swc1,swc2);

tmpImage=zeros(height,width);
inImage=zeros(height,width);
[lightArea,maxCoord,minCoord]=getLightArea(swc,R,imImf);
cropedWidth=maxCoord(1,1)-minCoord(1,1)+1;
cropedHeight=maxCoord(1,2)-minCoord(1,2)+1;  
outImage=zeros(cropedHeight+2*marginA,cropedWidth+2*marginA);

involvedZNum=size(lightArea,1);


for i=1:involvedZNum
    tic;
    tmpImage=zeros(height,width);
    pointOfZ=lightArea{i,1};
    z=pointOfZ(1,3);
    zSerial=z+zRange(1)-1;
    inImage=imread([src pre num2str(zSerial,'%05d') suf]);
    pointNumOfZ=size(pointOfZ,1);
    disp(zSerial);
%     tmpImage = zeros(size(inImage));
%     for j=1:pointNumOfZ
%         x=pointOfZ(j,1);
%         y=pointOfZ(j,2);
%         z=pointOfZ(j,3);
% %         outImage(y,x)=255;
%         tmpImage(y,x)=inImage(y,x);
%     end
    outImage(:,:)=inImage(minCoord(1,2)-marginA:maxCoord(1,2)+marginA,minCoord(1,1)-marginA:maxCoord(1,1)+marginA);
    outImage=uint8(outImage);
    imwrite(outImage,[dst num2str(i,'%05d') '.tif']);
    toc;
    disp(i);
end




toc;