clc;
clear all;

%  填入原始图片所在文件夹位置 注意：文件夹地址末尾要确保有\ 填写在下一行中的''内 
%  例如 文件夹位置为d盘src文件夹 
%  则下一行应为 src='D:\src\';
src='I:\process\montage\';
%  填入目标图片存放文件夹位置 注意：文件夹地址末尾要确保有\ 填写在下一行中的''内 
%  例如 存放位置为d盘dst文件夹
%  则下一行应为 dst='D:\dst\';
dst='I:\process\project\';
%  填入图片的宽度 例如 100; 则下一行应为 width=100;
width=20592;
%  填入图片的高度 例如 100; 则下一行应为 height=100;
height=51800;
%  填入切片的起始层数 例如 668 则下   一行应为 startZ=668;
startZ=162;
%  填入切片的终止层数 例如 1067 则下一行应为 endZ=1067;
endZ=167;
%  填入原始图片名的前缀 例如原始图片名为test_01258.tif 前后缀分别位于图片序号的五位数字两边
%  前缀是指test_ 后缀是指.tif 填写在下一行的''内
pre='test_';
%  填入原始图片名的后缀
post='_mon.tif';
%  填入投影的厚度，例如每100层投影一张，则下一行应为stackNum=100
stackNum=3;

zRange=[startZ,endZ];
inImage=uint8(zeros(height,width));
tmpImage=uint8(zeros(height,width));
index=1;
for i=zRange(1):zRange(2)
    if i == zRange(1)
        s = i;
    end
    inImage=imread([src pre num2str(i,'%05d') post]);
    disp(['reading ' src pre num2str(i,'%05d') post]);
    if index == stackNum || i == zRange(2)
        e = i;
        disp([dst pre num2str(s,'%05d') '-' num2str(e,'%05d') post]);
        imwrite(tmpImage, [dst pre num2str(s,'%05d') '-' num2str(e,'%05d') post]);
        index = 1;
        tmpImage=uint8(zeros(height,width));
        s = e + 1;
        continue;
    else
        tmpImage = max(tmpImage, inImage);
    end
    index=index+1;
end
