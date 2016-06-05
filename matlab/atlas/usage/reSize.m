clc;
clear all;
src='Y:\AppData\ZSQGroup\part1\TDI11107004\green\montage\';
pre='test_';
suf='_mon.tif';
dst='W:\rguo\TDI11107004\resample\0.2-0.2-1\';

files = dir(src);

for i= 3 : 6
    name = files(i, 1).name(1 : end - 4);
    disp(name);
    tic;
    I=imread([src name '.tif']);
    I=imresize(I, 0.15);
    imwrite(I,[dst name '_25.tif']);
    toc;
end


