clc;
clear all;

% 原图文件的路径
raw_src = 'W:\xhu\TDI11107004\resample\z25\';
% 原图文件的前缀
raw_pre = 'z25';
% 原图文件的后缀
raw_suf = '.tif';
% 二值化图文件的路径
result_src = 'W:\xhu\TDI11107004\resample\2d\';
% 二值化图文件的前缀
result_pre = '2d.';
% 二值化图文件的后缀
result_suf = '.tif';

image_num = 447;
for i = 0 : image_num - 1
    read_image_name = [raw_pre num2str(i, '%04d') raw_suf];
    read_image_path = [raw_src '\' read_image_name];
    b2_image_name = [result_pre num2str(i, '%04d') result_suf];
    b2_image_path = [result_src '\' b2_image_name];   
    a = imread(read_image_path);
    b = imread(b2_image_path);
    c = a.*b;
%     输出文件的路径    
    imwrite(c, ['W:\xhu\TDI11107004\resample\1\' num2str(i, '%05d') '.tif']);

end











% a = imread('W:\lsu\registration\TDI072\raw\resam-10176.tif');
% b = imread('W:\lsu\registration\TDI072\test\resam-10176.Labels.0000.tif');
% c = a.*b;
% 
% imwrite(c, 'W:\lsu\registration\TDI072\test\test.tif');