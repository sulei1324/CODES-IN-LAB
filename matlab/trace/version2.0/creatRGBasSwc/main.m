clc;

clear all;


height=34400;
width=23400;
zRange=6000;
swcNum=3;
pre='I9_part';
post='.swc';
R=8;
src='G:\sulei\allLong\';
dst='G:\sulei\allLong\rgb\';
rgbImageXZ=zeros(zRange,width);
rgbImageXZ=repmat(double((rgbImageXZ)./255),[1,1,3]);
rgbImageYZ=zeros(zRange,height);
rgbImageYZ=repmat(double((rgbImageYZ)./255),[1,1,3]);
rgbImageXY=zeros(height,width);
rgbImageXY=repmat(double((rgbImageXY)./255),[1,1,3]);
swc=[];

for i=1:swcNum
    tmp=load([src pre num2str(i,'%d') post]);
    tmp=tmp(:,3:5);
    swc=[swc;tmp];
end

rgbImageXY=creatRGB(swc,R,rgbImageXY,1,2);
rgbImageXZ=creatRGB(swc,R,rgbImageXZ,1,3);
rgbImageYZ=creatRGB(swc,R,rgbImageYZ,2,3);

rgbImageXY=imresize(rgbImageXY,0.1);
imshow(rgbImageXY);
imwrite(rgbImageXY,[dst 'XY.jpg']);
rgbImageXZ=imresize(rgbImageXZ,0.1);
imwrite(rgbImageXZ,[dst 'XZ.jpg']);
rgbImageYZ=imresize(rgbImageYZ,0.1);
imwrite(rgbImageYZ,[dst 'YZ.jpg']);


