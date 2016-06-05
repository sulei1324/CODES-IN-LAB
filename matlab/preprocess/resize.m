clc;
clear all;


%  填入重采样的比例，例如 0.3 则下一行应为 resize_ratio=0.3
resize_ratio = 0.06;
%  填入切片的起始层数 例如 668 则下一行应为 startZ=668;
startZ = 943;
%  填入切片的终止层数 例如 1067 则下一行应为 endZ=1067;
endZ = 946;
%  填入原始图片所在文件夹位置 注意：文件夹地址末尾要确保有\ 填写在下一行中的''内 
%  例如 文件夹位置为d盘src文件夹 
%  则下一行应为 src='D:\src\';
src='I:\process\montage\';
%  填入目标图片存放文件夹位置 注意：文件夹地址末尾要确保有\ 填写在下一行中的''内 
%  例如 存放位置为d盘dst文件夹
%  则下一行应为 dst='D:\dst\';
dst='I:\process\resize\';
%  填入原始图片名的前缀 例如原始图片名为test_01258.tif 前后缀分别位于图片序号的五位数字两边
%  前缀是指test_ 后缀是指.tif 填写在下一行的''内
pre='test_';
%  填入原始图片名的后缀
post='_mon.tif';

tmpImage=imread([src pre num2str(startZ,'%05d') post]);
[rawImageHeight,rawImageWidth]=size(tmpImage);
clear tmpImage;
wPre='test_';
wPost='.tif';
inImage=uint8(zeros(rawImageHeight,rawImageWidth));
for i=startZ:endZ
    inImage=imread([src pre num2str(i,'%05d') post]);
    disp(['reading ' num2str(i,'%05d') ' image']);
    outImage=imresize(inImage, resize_ratio);
    outImage = uint8(outImage);
    disp(['writing ' num2str(i,'%05d') ' image'])
    imwrite(outImage,[dst wPre num2str(i,'%05d') '_res' wPost]);
end

    
