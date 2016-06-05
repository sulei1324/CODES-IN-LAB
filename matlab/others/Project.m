clc;

clear all;

srcFile='Y:\Public\mostPreprocess\TDI079\green\project100\';
dstFile='W:\lsu\movie\11-6movie\part5\';

pre='test_';
suf='_x3500_y_17200_w_4000_h_6600.tif';

zRange=[1578,3424];
thick=zRange(1,2)-zRange(1,1)+1;
width=4000;
height=6600;

inImage=zeros(height,width);
tmp=zeros(width,height);
pXY=zeros(height,width);
pXZ=zeros(thick,width);
pYZ=zeros(thick,height);



for i=zRange(1):zRange(2)
    tic;
    disp(['reading ' num2str(i) ' image']);
    inImage(:,:)=imread([srcFile  pre num2str(i,'%05d') suf]);
    disp(['Project ' num2str(i) ' xy']);
    pXY=max(pXY,inImage);
%     disp(['Project ' num2str(i) '  xz']);
%     pXZ(i-zRange(1)+1,:)=max(inImage);
%     disp(['Project ' num2str(i) '  yz']);
%     pYZ(i-zRange(1)+1,:)=max(inImage');
    toc;
end

pXY=uint8(pXY);
% pXZ=uint8(pXZ);
% pYZ=uint8(pYZ);
imwrite(pXY,[dstFile  'I2_XYProject.tif']);
% imwrite(pXZ,[dstFile num2str(zRange(1)) 'to' num2str(zRange(2))  'XZProject.tif']);
% imwrite(pYZ,[dstFile num2str(zRange(1)) 'to' num2str(zRange(2))  'YZProject.tif']);


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






