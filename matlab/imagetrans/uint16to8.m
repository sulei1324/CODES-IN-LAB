clc;
clear all;

src = 'W:\lsu\TDI21107006\crop1\';
dst = 'W:\lsu\TDI21107006\uint8\';
zRange = [516, 1316];
imPre = 'test_';
imPost = '_x5944_y13682_w8000_h6000.tif';
max_outImage = 100;
max_outImage = 0;

for i = zRange(1) : zRange(2)
    inImage = imread([src imPre num2str(i, '%05d') imPost]);
    max_inImage = max(max(inImage));
    min_inImage = min(min(inImage));
    [height, width] = size(inImage);
    tmpImage = double(inImage - min_inImage);
    tmpImage = tmpImage * 255 / double(max_inImage - min_inImage);  
    outImage = uint8(tmpImage);
    imwrite(outImage, [dst 'test_' num2str(i, '%05d') '_adj.tif']);
end