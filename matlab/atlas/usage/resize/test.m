clc;

clear all;
% 
raw_image = imread('C:\Users\ËÕÀ×\Desktop\test_04864-04888.tif');
res_image = imresize(raw_image, 0.012, 'nearest');
imwrite(res_image, 'res3\nearest.tif');
res_image = imresize(raw_image, 0.012, 'bilinear');
imwrite(res_image, 'res3\bilinear.tif');
res_image = imresize(raw_image, 0.012, 'bicubic');
imwrite(res_image, 'res3\bicubic.tif');
res_image = imresize(raw_image, 0.012, 'box');
imwrite(res_image, 'res3\box.tif');
res_image = imresize(raw_image, 0.012, 'triangle');
imwrite(res_image, 'res3\triangle.tif');
res_image = imresize(raw_image, 0.012, 'cubic');
imwrite(res_image, 'res3\cubic.tif');
res_image = imresize(raw_image, 0.012, 'lanczos2');
imwrite(res_image, 'res3\lanczos2.tif');
res_image = imresize(raw_image, 0.012, 'lanczos3');
imwrite(res_image, 'res3\lanczos3.tif');