clc;
clear all;

image = imread('00001-2-2.tif');
image = double(image);
minValue = 0;
maxValue = 220;
[height, width] = size(image);
for i = 1:height
    for j = 1:width
        image(i, j)  = round(((image(i ,j) - minValue) / (maxValue - minValue)) * 255);
        if image(i, j) > 255
            image(i, j) = 255;
        else if image(i, j) < 0
                image(i, j) = 0;
            end
        end
    end
end

image = uint8(image);
imwrite(image, 'a.tif');
imshow(image);

