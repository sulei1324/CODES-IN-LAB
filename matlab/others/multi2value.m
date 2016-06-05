clc;
clear all;

src1 = 'W:\lsu\TDI11302020\red\10\';
src2 = 'W:\lsu\TDI11302020\red\10c\';
dst = 'W:\lsu\TDI11302020\red\10u\';

src1_pre = 'test_';
src1_post = '_res.tif';
src2_pre = 'test_00100_res.';
src2_post = '.tif';
src1_beg = 100;
src1_end = 4850;
src2_beg = 0;
src2_end = 475;
src2_index = src2_beg;
for i = src1_beg :10 : src1_end
   disp(i);
   im1 = imread([src1 src1_pre num2str(i, '%05d') src1_post]);
   im2 = imread([src2 src2_pre num2str(src2_index, '%04d') src2_post]);
   im3 = im1 .* im2;
   imwrite(im3, [dst 'test_' num2str(i, '%05d') '_used.tif']); 
   src2_index = src2_index + 1; 
end

