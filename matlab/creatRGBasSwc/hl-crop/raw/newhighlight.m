% function newhighlight()


clear all;
clc;
tic;

width=23400;
height=32200;
zRange=[101,6100];
level=zRange(2)-zRange(1)+1;
imImf=[width,height,level];
src=('W:\lsu\movie\I5\I5_end_sub\adj\');
dst=('W:\lsu\movie\I5\I5_end_sub\highlight\');
pre='adjI5_end';
suf='.bmp';
R=10;
swc=load('W:\lsu\anlysis\I9\I9_X3-X4.swc');
% swc1=load('Z:\jli\YFP12002_manualTrace\4101_4500_lijing\4101_4500-bright2_manual.swc');
% swc2=load('Z:\jli\YFP12002_manualTrace\4101_4500_lijing\4101_4500-bright5_manual.swc');
% swc = MergeTwoSwc(swc1,swc2);

tmpImage=zeros(height,width);
inImage=zeros(height,width);
[lightArea,maxCoord,minCoord]=getLightArea(swc,R,imImf);
cropedWidth=maxCoord(1,1)-minCoord(1,1)+1;
cropedHeight=maxCoord(1,2)-minCoord(1,2)+1;  
outImage=zeros(cropedHeight,cropedWidth);

involvedZNum=size(lightArea,1);


% for i=1:involvedZNum
%     tic;
%     tmpImage=zeros(height,width);
%     pointOfZ=lightArea{i,1};
%     z=pointOfZ(1,3);
%     zSerial=z+zRange(1)-1;
%     inImage=imread([src pre num2str(zSerial,'%04d') suf]);
%     pointNumOfZ=size(pointOfZ,1);
%     disp(zSerial);
%     tmpImage = zeros(size(inImage));
%     for j=1:pointNumOfZ
%         x=pointOfZ(j,1);
%         y=pointOfZ(j,2);
%         z=pointOfZ(j,3);
% %         outImage(y,x)=255;
%         tmpImage(y,x)=inImage(y,x);
%     end
%     outImage(:,:)=tmpImage(minCoord(1,2):maxCoord(1,2),minCoord(1,1):maxCoord(1,1));
%     outImage=uint8(outImage);
%     imwrite(outImage,[dst num2str(i,'%05d') '.tif']);
%     toc;
%     disp(i);
% end




toc;