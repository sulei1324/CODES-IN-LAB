clc;
clear all;

swc_src = 'W:\xhu\TDI072\transSwc_all\bouttons\swc1';
csv_src = 'W:\xhu\TDI072\transSwc_all50\bouttons\csv1';
dst = 'W:\xhu\TDI072\transSwc_all50\bouttons\swc1';
% swc0,csv2,swc1文件夹的路径
swc_files = dir(swc_src);
for i = 3 : size(swc_files, 1)
    swc_name = swc_files(i, 1).name;
    swc_id = swc_name(1 : end - 6);
    csv_name = [swc_id '_1.csv'];
    swc = load([swc_src '\\' swc_name]);
    csv = csvread([csv_src '\\' csv_name], 1, 0);
    swc(:, 3 : 5) = csv(:, 1 : 3);
    dlmwrite([dst '\\' swc_id '_1.swc'], swc, 'delimiter', ' ',  'newline','pc');
end
