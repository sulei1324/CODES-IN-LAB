clc;
clear all;


%  填入切片在原始图片中的起始x坐标 例如 1111 则下一行应为 startX=1111;
startX=17803;
%  填入切片在原始图片中的起始y坐标 例如 1111 则下一行应为 startY=1111;
startY=19603;
%  填入切片的宽度 例如 100; 则下一行应为 width=100;
width=508;
%  填入切片的高度 例如 100; 则下一行应为 height=100;
height=499;
%  填入切片的起始层数 例如 668 则下一行应为 startZ=668;
startZ=3333;
%  填入切片的终止层数 例如 1067 则下一行应为 endZ=1067;
endZ=22222;
%  填入原始图片所在文件夹位置 注意：文件夹地址末尾要确保有\ 填写在下一行中的''内 
%  例如 文件夹位置为d盘src文件夹 
%  则下一行应为 src='D:\src\';
src='Y:\Public\mostPreprocess\TDI072\montage\';
%  填入目标图片存放文件夹位置 注意：文件夹地址末尾要确保有\ 填写在下一行中的''内 
%  例如 存放位置为d盘dst文件夹
%  则下一行应为 dst='D:\dst\';
dst='G:\sulei\workplace\Swc\test2\';
%  填入原始图片名的前缀 例如原始图片名为test_01258.tif 前后缀分别位于图片序号的五位数字两边
%  前缀是指test_ 后缀是指.tif 填写在下一行的''内
pre='test_';
%  填入原始图片名的后缀
post='_mon.tif';
wPre='test_';
wPost='_crop.tif';



tmpImage=imread([src pre num2str(startZ,'%05d') post]);
[rawImageHeight,rawImageWidth]=size(tmpImage);
clear tmpImage;
wMid=['_x' num2str(startX) '_y' num2str(startY) '_w' num2str(width) '_h' num2str(height)];
inImage=uint16(zeros(rawImageHeight,rawImageWidth));
outImage=uint16(zeros(height,width));
for i=startZ:endZ
    inImage=imread([src pre num2str(i,'%05d') post]);
    disp(['reading ' num2str(i,'%05d') ' image']);
    outImage=inImage(startY:startY+height-1,startX:startX+width-1);
    disp(['writing ' num2str(i,'%05d') ' image'])
    imwrite(outImage,[dst wPre num2str(i,'%05d') wMid wPost]);
end

    
