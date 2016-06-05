% function cropAsSwc()
clc;
clear all;

tic;
width=5072;
height=7000;
zRange=[768,1867];
imageImf=[width;height;zRange(1);zRange(2)];
level=zRange(2)-zRange(1)+1;

src=('Y:\Public\mostgroup\data_us\MBA-GF13004_cut\12-16_with_LDA\');
dst=('Y:\Public\mostgroup\data_us\MBA-GF13004_cut\LDA\12-16\12_16-files\axonNearCellRaw\');
pre='test_';
suf='_x5142_y_20000_w_5072_h_7000.tif';
R=8;

swc=load('G:\sulei\I9\count\figure\cell\cell.swc');
swc(:,3:4)=swc(:,3:4)*10/3;
line=readLine(swc);
lineNum=size(line,1);


blockMax=[];
blockMin=[];
[blockMax,blockMin]=showMaxLocation(swc,R,imageImf);


newZrange=[blockMin(1,3)+zRange(1)-1,blockMax(1,3)+zRange(1)-1];
newLevel=newZrange(2)-newZrange(1)+1;
newWidth=blockMax(1,1)-blockMin(1,1)+1;
newHeight=blockMax(1,2)-blockMin(1,2)+1;




% tmp=zeros(height,width);
% I=zeros(newHeight,newWidth);
% for i=newZrange(1):newZrange(2)
% 
%     disp(i);
%     
%     tmp=imread([src pre num2str(i,'%05d') suf]);
%     I(:,:)=tmp(blockMin(1,2):blockMax(1,2),blockMin(1,1):blockMax(1,1));
%     I=uint8(I);
%     imwrite(I,[dst 'crop_' num2str(i,'%05d') '.tif']);
%     
% end
toc;




% % ball=sphericalArea(R);
% % Range=[newZrange(1)-zRange(1)+1,newZrange(2)-zRange(1)+1];
% % 
% % Range=Range-1;
% % Image=zeros(newHeight,newWidth,newLevel);
% % tmpImage=zeros(newHeight,newWidth,newLevel);
% % tmpImage(:,:,i)=imread('Y:\Public\mostzhangyalun\sulei\thy1\59_CROP_RESIZE\used.tif',i);