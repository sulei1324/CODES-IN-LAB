clc;
clear all;

swc1 = load('W:\xhu\020-072\transSwc\b\SpatialGraph1.swc');
swc2 = swc1;
shift1 = [15920, 23383, 1088, 1636, 1340, 479];
for i = 1 : size(swc1, 1)
    swc2(:, 3) = swc1(:, 3) + shift1(1) * 0.3;
    swc2(:, 4) = swc1(:, 4) + shift1(2) * 0.3;
    swc2(:, 5) = swc1(:, 5) + shift1(3);
end
dlmwrite('W:\xhu\020-072\transSwc\b\bb10.swc', swc2, 'delimiter', ' ', 'newline', 'pc');