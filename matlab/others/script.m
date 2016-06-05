clc;
clear all;

src='G:\sulei\13004\allproject\';
pre='test_';
post='_correct.tif';
dst='G:\sulei\13004\newproject\';
a=size(pre,2);
b=size(post,2);
f=dir(src);
fNum=size(f,1);
fImage=zeros(32200,23400);
sImage=zeros(32200,23400);
for i=3:2:fNum
    fImage=imread([src f(i).name]);
    sImage=imread([src f(i+1).name]);
    fNum=f(i).name(a+1:a+5);
    sNum=f(i+1).name(a+1:a+5);
    disp(['reading ' f(i).name]);
    disp(['reading ' f(i+1).name]);
    fImage=max(fImage,sImage);
    fImage=uint8(fImage);
    imwrite(fImage,[dst 'pro_' fNum '-' sNum '.tif']);
    disp(['writing ' 'pro_' fNum '-' sNum '.tif']);
end

