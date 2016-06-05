clc;
clear all;


src='G:\sulei\13004\newproject\';
dst='G:\sulei\13004\net\';
pre='pro_';
mid='-';
post='.tif';
zRange=[1068,5968];
width=23400;
height=32200;

for i=zRange(1):100:zRange(2)
    imageName=[pre num2str(i,'%05d') mid num2str(i+50,'%05d') post];
    disp(['checking ' imageName]);
    finfo=imfinfo([src imageName]);
    if(finfo.Width~=width)
        system(['copy' ' ' src imageName ' ' dst]);
    else
        inImage=imread([src imageName]);
        inImage=inImage';
        inImage=uint8(inImage);
        imwrite(inImage,[dst imageName]);
    end
end