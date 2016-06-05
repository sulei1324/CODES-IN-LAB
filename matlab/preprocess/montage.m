clc;
clear all;

%  填入原始图片所在文件夹位置 注意：文件夹地址末尾要确保有\ 填写在下一行中的''内 
%  例如 文件夹位置为d盘src文件夹 
%  则下一行应为 src='D:\src\';
src = 'I:\process\raw\';
%  填入目标图片存放文件夹位置 注意：文件夹地址末尾要确保有\ 填写在下一行中的''内 
%  例如 存放位置为d盘dst文件夹
%  则下一行应为 dst='D:\dst\';
dst = 'I:\process\montage\';
%  填入切片的起始层数 例如 668 则下   一行应为 startZ=668;
start_serial = 162;
%  填入切片的终止层数 例如 1067 则下一行应为 endZ=1067;
end_serial = 167;
%  填入原始图片名的前缀 例如原始图片名为test_01258.tif 前后缀分别位于图片序号的五位数字两边
%  前缀是指test_ 后缀是指.tif 填写在下一行的''内
pre = 'test__';
%  填入原始图片名的后缀
post = '.png';
%  填入帧图像的起始和终止的xy序号
x_beg = 40;
y_beg = 31;
x_end = 55;
y_end = 67;
%  填入帧图像的宽度
block_width = 1287;
%  填入帧图像的高度
block_height = 1400;





whole_image = zeros(block_height * (y_end - y_beg + 1), block_width * (x_end - x_beg + 1));
whole_image = uint8(whole_image);
for i = start_serial : end_serial
   serial_src = [src num2str(i, '%05d') '\'];
   dst_image_name = [dst 'test_' num2str(i, '%05d') '_mon.tif'];
   disp(serial_src);
   for j = x_beg : x_end
       for k = y_beg : y_end
           image_name = [serial_src pre num2str(i, '%05d') '_' num2str(j, '%02d') '_' num2str(k, '%02d') post];
           disp(image_name);
           block_image = imread(image_name);
           block_image = block_image(:, end: -1 :1);           
           whole_image((k-y_beg) * block_height + 1 : (k - y_beg + 1) *block_height, (j-x_beg) * block_width + 1 : (j-x_beg + 1) *block_width) = block_image(:, :);                 
       end
   end
   imwrite(whole_image, dst_image_name);
end

