clc;

clear all;

src='W:\lsu\movie\11-6movie\hippo\hippo-crop\';
dst='W:\lsu\movie\book\part5\hippo_pro2\';
width=1884;
height=1452;
zRange=[0,212];
pre='hippo_';
post='.tif';
inImage=uint16(zeros(height,width));
tmpImage=uint16(zeros(height,width));

stackNum=50;

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
        tmpImage=uint16(zeros(height,width));
        s = e + 1;
        continue;
    else
        tmpImage = max(tmpImage, inImage);
    end
    index=index+1;
end
