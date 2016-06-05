clc;
clear all;


inImage = uint16([6622, 3000, 200]);
max_inImage = max(max(inImage));
min_inImage = min(min(inImage));
max_outImage = 255;
max_outImage = 0;
[height, width] = size(inImage);
tmpImage = double(inImage - min_inImage);
tmpImage = tmpImage * 255 / double(max_inImage - min_inImage); 
outImage = uint8(tmpImage);
    

