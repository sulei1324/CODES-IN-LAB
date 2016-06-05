clc;

clear all;

srcFile='Y:\Archive\MBA-GF13004_preprocess\Src_Pro\allproject\';
dstFile='W:\lsu\figure3\';

pre='test_';
suf='.tif';

zRange=[101,121];
thick=zRange(1,2)-zRange(1,1)+1;
width=23400;
height=32200;



f=dir(srcFile);
numF=size(f,1);


inImage=zeros(height,width);
pXY=zeros(height,width);



for i=3:numF
    tic;
    imageName=f(i).name;
    disp(['reading ' imageName]);
    inImage(:,:)=imread([srcFile  imageName]);
    pXY=max(pXY,inImage);
    toc;
end

pXY=uint8(pXY);
imwrite(pXY,[dstFile  'XYProject.tif']);


% inImage=tempImage;

% labelNum=zRange(2)-zRange(1)+1;
% WZProject=zeros(width,labelNum);
% 
% for i=zRange(1):zRange(2)
%     WZProject(:,i)=max(inImage(:,:,i));
% end
% 
% HZProject=zeros(height,zRange);
% 
% for i=zRange(1):zRange(2)
%     tempImage(:,:,i)=inImage(:,:,i)';
%     HZProject(:,i)=max(tempImage(:,:,i));
% end
% 
% WHProject=zeros(width,height);
% 
% tempImage=permute(inImage,[3 2 1]);
% 
% for i=1:height
%     WHProject(:,i)=max(tempImage(:,:,i));
% end
% 
% WZProject=uint8(WZProject);
% HZProject=uint8(HZProject);
% WHProject=uint8(WHProject);






