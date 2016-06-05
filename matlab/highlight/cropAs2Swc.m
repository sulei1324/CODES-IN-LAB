clc;
clear all;

tic;
width=5072;
height=7000;
zRange=[768,1867];
imageImf=[width;height;zRange(1);zRange(2)];
level=zRange(2)-zRange(1)+1;

src=('Y:\Public\mostgroup\data_us\MBA-GF13004_cut\12-16_with_LDA\');
dst=('Y:\Public\mostgroup\data_us\MBA-GF13004_cut\LDA\12-16\12_16-files\crop1\');
pre='test_';
suf='_x5142_y_20000_w_5072_h_7000.tif';
R=8;


swc1=load('Y:\Public\mostgroup\data_us\MBA-GF13004_cut\LDA\12-16\12_16-files\SpatialGraph1.swc');
swc1(:,3:4)=swc1(:,3:4)*10/3;
line1=readLine(swc1);
lineNum1=size(line1,1);
blockMax1=[];
blockMin1=[];
[blockMax1,blockMin1]=showMaxLocation(swc1,R,imageImf);

swc2=load('Y:\Public\mostgroup\data_us\MBA-GF13004_cut\LDA\12-16\12_16-files\SpatialGraph1_axon.swc');
swc2(:,3:4)=swc2(:,3:4)*10/3;
line2=readLine(swc2);
lineNum2=size(line2,1);
blockMax2=[];
blockMin2=[];
[blockMax2,blockMin2]=showMaxLocation(swc2,R,imageImf);

[totalMax,totalMin]=totalMaxMin(blockMax1,blockMax2,blockMin1,blockMin2);

% ball=sphericalArea(R);


newZrange=[totalMin(1,3)+zRange(1)-1,totalMax(1,3)+zRange(1)-1];
newLevel=newZrange(2)-newZrange(1)+1;
newWidth=totalMax(1,1)-totalMin(1,1)+1;
newHeight=totalMax(1,2)-totalMin(1,2)+1;



% Image=zeros(newHeight,newWidth,newLevel);
% tmpImage=zeros(newHeight,newWidth,newLevel);
tmp=zeros(height,width);
I=zeros(newHeight,newWidth);




% Range=[newZrange(1)-zRange(1)+1,newZrange(2)-zRange(1)+1];
% 
% Range=Range-1;

for i=newZrange(1):newZrange(2)
%     tmpImage(:,:,i)=imread('Y:\Public\mostzhangyalun\sulei\thy1\59_CROP_RESIZE\used.tif',i);
    disp(i);
    tic;
    tmp=imread([src pre num2str(i,'%05d') suf]);
    I(:,:)=tmp(totalMin(1,2):totalMax(1,2),totalMin(1,1):totalMax(1,1));
    I=uint8(I);
    imwrite(I,[dst 'crop_' num2str(i,'%05d') '.tif']);
    toc;
end
toc;