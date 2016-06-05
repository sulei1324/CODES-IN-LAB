clc;
clear all;


a = [0, 255, 100; 244, 30, 99];
a((a >= 100)) = 255;
a(a < 100) = a(a < 100) * 255 / 100;


src = 'W:\lsu\TDI21107006\uint8\';
dst = 'W:\lsu\TDI21107006\adj\';
zRange = [516, 1316];
imPre = 'test_';
imPost = '_adj.tif';
max_outImage = 100;
max_outImage = 0;

for i = zRange(1) : zRange(2)
    inImage = imread([src imPre num2str(i, '%05d') imPost]);
    tmpImage = inImage;
    tmpImage((tmpImage >= 100)) = 255;
    tmpImage(tmpImage < 100) = tmpImage(tmpImage < 100) * 255 / 100;
    outImage = uint8(tmpImage);
    imwrite(outImage, [dst 'test_' num2str(i, '%05d') '_adj100.tif']);
end
