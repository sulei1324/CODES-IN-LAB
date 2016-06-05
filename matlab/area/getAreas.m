clc;
clear all;

src = 'W:\lsu\TDI072\contour-olfactory bulb\sl\crop\outline.tif';
z_range = [0, 45];
areas = [];

for i = z_range(1) : z_range(2)
    disp(i);
    image1 = imread(src, 'Index', i + 1);
    area1 = size(find(image1 ~= 0), 1);
    areas = [areas; area1];
end  