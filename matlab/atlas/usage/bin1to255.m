clc;
clear all;

w = 456;
h = 320;
t = 528;
a = 'W:\xhu\test\3\Allen_Nissl_points.tif';
b = 'W:\xhu\test\3\syn_diff_points.tif';
a_dst = 'W:\xhu\test\3\tmp\s\';
b_dst = 'W:\xhu\test\3\tmp\a\';
a_images = zeros(h, w, t);
b_images = zeros(h, w, t);
for i = 1 : t
   a_images(:, :, i) = imread(a, i); 
   b_images(:, :, i) = imread(b, i);
end

a_not_zeros = find(a_images ~= 0);
b_not_zeros = find(b_images ~= 0);

a_images(a_not_zeros) = 255;
b_images(b_not_zeros) = 255;

an = size(a_not_zeros, 1);
bn = size(b_not_zeros, 1);

for i = 1 : t
   imwrite(a_images(:, :, i), [a_dst 'a_' num2str(i, '%05d') '.tif']); 
   imwrite(b_images(:, :, i), [b_dst 'b_' num2str(i, '%05d') '.tif']);
end



