clc;
clear all;

zRange=[3896,7334];
src='Y:\Public\mostPreprocess\MBA-GF13004_compress\resample10x\';
dst='W:\lsu\13004_10x\';
readPre='test_';
readPost='_correct.tif';
writePre='page_';
writePost='.tif';
fontBold=10;
width=2340;
height=3440;
textLoc1=2250;
textLoc2=3200;
inImage=zeros(height,width);
tmpImage=zeros(width,height);


for i=zRange(1):zRange(2)
    pageNum=i-18+1;
    pageImage=creatNumImage(pageNum,fontBold);
    pageImage=uint8(pageImage);
    imshow(pageImage);
    x=num2str(i,'%05d');
    inImage=imread([src readPre x readPost]);
    tmpImage=inImage';
    [m,n]=size(pageImage);
    tmpImage(textLoc1-m+1:textLoc1,textLoc2-n+1:textLoc2)=pageImage(:,:);
    tmpImage=uint8(tmpImage);
    imwrite(tmpImage,[dst writePre num2str(pageNum,'%05d') writePost]);
    clc;
    percentShow1=(pageNum/(zRange(2)-zRange(1)+1))*100;
    percentShow2=num2str(percentShow1,'%.2f');
    disp(['already done ' percentShow2 '%']);
end



    
    