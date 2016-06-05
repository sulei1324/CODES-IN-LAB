clc;
clear all;

raw_src = 'W:\lsu\registration\TDI072\raw\';
raw_pre = 'resam-1';
raw_suf = '.tif';
result_src = 'W:\lsu\registration\TDI072\test\';
result_pre = 'resam-10176.Labels.';
result_suf = '.tif';
image_num = 475;

for i = 0 : image_num - 1
    read_image_name = [raw_pre num2str(i, '%04d') raw_suf];
    read_image_path = [raw_src '\' read_image_name];
    disp(read_image_name);
    disp([raw_src '\' read_image_name]);
    a = imread(read_image_path);
    b = imread(read_image_path);
    c = a.*b;
    imwrite(c, ['W:\lsu\registration\TDI072\test\' num2str(i, '%05d') '.tif']);
    
    
end











% a = imread('W:\lsu\registration\TDI072\raw\resam-10176.tif');
% b = imread('W:\lsu\registration\TDI072\test\resam-10176.Labels.0000.tif');
% c = a.*b;
% 
% imwrite(c, 'W:\lsu\registration\TDI072\test\test.tif');