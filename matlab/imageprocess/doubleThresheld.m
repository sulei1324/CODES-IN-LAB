clc;
clear all;

image = imread('2.tif');
threshed1 = 50;
threshed2 = 200;
[height, width] = size(image);
for i = 1:height
    for j = 1:width
        if image(i, j) >200 || image(i, j) <50
            image(i, j) = 0;
        else
            image(i, j) = 255;
        end
    end
end

imshow(image);