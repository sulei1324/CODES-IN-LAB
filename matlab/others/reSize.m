clc;
clear all;
src='Y:\AppData\ZSQGroup\part3\TDI21301006-1\R\resample\';
pre='test_';
suf='_res.tif';
dst='W:\xhu\TDI21301006\raw_25\';

files = dir(src);

for i=3 : size(files, 1)
    name = files(i, 1).name(1 : end - 4);
    disp(name);
    
    tic;
    I=imread([src name '.tif']);
    I=imresize(I, 0.12);
    imwrite(I,[dst name '_25.tif']);
    toc;
end


