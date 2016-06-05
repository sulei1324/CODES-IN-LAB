clc;

clear all;

zRange=[1481,2000];

srcFile='Y:\Public\mostgroup\data_us\AAV-YFP';

dstFile='Y:\Public\mostzhangyalun\sulei\matlab\test_dst\100xresample';

pre='test_';
suf='_montage.tif';

resampleRatio=0.01;

tic;
for i=zRange(1):zRange(2)
    inImage=imread([srcFile '\' pre num2str(i,'%05d') suf]);
    outImage=imresize(inImage,resampleRatio);
    imwrite(outImage,[dstFile '\' '10x_' num2str(i,'%05d') suf]);
end
toc;
