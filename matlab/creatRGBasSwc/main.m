clc;
clear all;
tic;
width=234000;
height=32200;
zRange=[101,6100];
level=zRange(2)-zRange(1)+1;
imImf=[width,height,level];
dst='W:\lsu\allLong\tmp\';
R=1;
swc1=load('W:\lsu\B3_21\15_transformed.swc');
% swc2=load('W:\lsu\movie\11-6movie\part5\I2_axon.swc');
% swc3=load('W:\lsu\movie\11-6movie\part5\I2_den.swc');
outImage=zeros(height,width);
outImage=repmat(double((outImage)./255),[1,1,3]);

lightArea1=getLightArea(swc1,R,imImf);
involvedZNum1=size(lightArea1,1);
for i=1:involvedZNum1
    disp(1);
    pointOfZ=lightArea1{i,1};
    pointNumOfZ=size(pointOfZ,1);
    outImage=creatRGB(pointOfZ,outImage,[1,0,0]);   
%     imshow(outImage);
    disp(i);
end

% lightArea2=getLightArea(swc2,R,imImf);
% involvedZNum2=size(lightArea2,1);
% for i=1:involvedZNum2
%     pointOfZ=lightArea2{i,1};
%     pointNumOfZ=size(pointOfZ,1);
%     outImage=creatRGB(pointOfZ,outImage,[0,1,0]);   
% 
%     disp(i);
% end
% 
% 
% lightArea3=getLightArea(swc3,R,imImf);
% involvedZNum3=size(lightArea3,1);
% for i=1:involvedZNum3
%     pointOfZ=lightArea3{i,1};
%     pointNumOfZ=size(pointOfZ,1);
%     outImage=creatRGB(pointOfZ,outImage,[0,1,0]);   
% 
%     disp(i);
% end


imwrite(outImage,[dst  'I7_cell.tif']);



% swcNum=1;
% pre='7-10-';
% post='.swc';
% R=8;
% src='W:\lsu\movie\11-6movie\neutron\7-10-1\';
% dst='W:\lsu\movie\11-6movie\neutron\7-10-1\';
% rgbImageXZ=zeros(zRange,width);
% rgbImageXZ=repmat(double((rgbImageXZ)./255),[1,1,3]);
% rgbImageYZ=zeros(zRange,height);
% rgbImageYZ=repmat(double((rgbImageYZ)./255),[1,1,3]);
% rgbImageXY=zeros(height,width);
% rgbImageXY=repmat(double((rgbImageXY)./255),[1,1,3]);
% swc=[];
% 
% for i=1:swcNum
%     tmp=load([src pre num2str(i,'%d') post]);
%     tmp=tmp(:,3:5);
%     swc=[swc;tmp];
% end
% 
% rgbImageXY=creatRGB(swc,R,rgbImageXY,3,width,height,zRange);
% rgbImageXZ=creatRGB(swc,R,rgbImageXZ,2,width,height,zRange);
% rgbImageYZ=creatRGB(swc,R,rgbImageYZ,1,width,height,zRange);
% 
% % rgbImageXY=imresize(rgbImageXY);
% imshow(rgbImageXY);
% imwrite(rgbImageXY,[dst 'XY.jpg']);
% % rgbImageXZ=imresize(rgbImageXZ);
% imwrite(rgbImageXZ,[dst 'XZ.jpg']);
% % rgbImageYZ=imresize(rgbImageYZ);
% imwrite(rgbImageYZ,[dst 'YZ.jpg']);


