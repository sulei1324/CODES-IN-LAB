clc;
clear all;

startX=14000;
startY=25000;
width=1300;
height=1500;
startZ=4701;
endZ=5000;
rawImageWidth=23400;
rawImageHeight=36400;
src='Y:\Public\mostPreprocess\TDI11301005\green\montage\';
dst='W:\rguo\auto\';

pre='test_';
post='_mon.tif';

wPre='test_';
wMid=['_x' num2str(startX) '_y' num2str(startY) '_w' num2str(width) '_h' num2str(height)];
wPost='.tif';


inImage=uint16(zeros(rawImageHeight,rawImageWidth));
outImage=uint16(zeros(height,width));
for i=startZ:endZ
    if i < 4855
        continue;
    end
    inImage=imread([src pre num2str(i,'%05d') post]);
    disp(['reading ' num2str(i,'%05d') ' image']);
    outImage=inImage(startY:startY+height-1,startX:startX+width-1);
    disp(['writing ' num2str(i,'%05d') ' image'])
    imwrite(outImage,[dst wPre num2str(i,'%05d') wMid wPost]);
end


    
