clc;

clear all;
tic;
src='W:\lsu\movie\I5\I5_cell\';
dst='W:\lsu\movie\I5\cell_pro\';
width=472;
height=904;
zRange=[1,154];
pre='';
post='.tif';
stackNum=12;


inImage=uint16(zeros(height,width));
tmpImage=uint16(zeros(height,width));
outImage=uint16(zeros(height,width));



index=1;
for i=zRange(1):zRange(2)
    index=index+1;
    inNum=i;
    tmpImage=proByNum(inNum,stackNum,src,pre,post,width,height);
    outImage=tmpImage;
    outImage=uint8(outImage);        
    imwrite(outImage,[dst 'pro' num2str(i,'%05d') post]);
end
toc;