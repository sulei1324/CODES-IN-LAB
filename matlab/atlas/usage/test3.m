clc;
clear all;
w = 23760;
h = 35000;
swc_25src = 'W:\xhu\020-072\transSwc\bt\swc1';
swc_1dst = 'W:\xhu\020-072\transSwc\1swc\b';

swc_25s = dir(swc_25src);
for i = 3 : size(swc_25s, 1)
   swc_i = swc_25s(i, 1).name;
   swc_25_i = load([swc_25src '\' swc_i]);
   swc_1_i = swc_25_i;
   t_y = swc_25_i(:, 4);
   swc_1_i(:, 4) = swc_25_i(:, 3) * 25;
   swc_1_i(:, 3) = w * 0.3 - t_y * 25;
   swc_1_i(:, 5) = swc_25_i(:, 5) * 25 + 7945;
   dlmwrite([swc_1dst '\1um_' swc_i], swc_1_i, 'delimiter', ' ', 'newline', 'pc');
end



