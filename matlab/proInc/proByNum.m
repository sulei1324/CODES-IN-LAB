function [tmpImage]=proByNum(startNum,stackNum,src,pre,post,width,height)

zRange=zeros(1,2);
zRange(1)=startNum;
zRange(2)=startNum+stackNum-1;
inImage=uint8(zeros(height,width));
tmpImage=uint8(zeros(height,width));

disp(['projecting ' num2str(zRange(1),'%05d') ' to ' num2str(zRange(2),'%05d')]);
for i=zRange(1):zRange(2)
    inImage=imread([src pre num2str(i,'%05d') post]);   
    tmpImage=max(tmpImage,inImage);
end

tmpImage=uint8(tmpImage);