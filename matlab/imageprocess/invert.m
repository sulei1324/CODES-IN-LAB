clc;
clear all;

image = imread('2.tif');
[height, width] = size(image);
for i = 1:height
    for j = 1:width
        image(i, j) = 255 - image(i, j);
    end
end

imshow(image);