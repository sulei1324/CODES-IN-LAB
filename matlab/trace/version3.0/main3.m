clc;
clear all;
tic;
swc=load('I9.swc');
src='Y:\Public\mostPreprocess\MBA-GF13004_compress\correct\';
dst='W:\lsu\matlab\test_dst\trace\3\';
width=23400;
height=32200;
outWidth=1000;
outHeight=618;
zRange=[101,6100];
pre='test_';
suf='_correct.tif';
interval=30;
% overlap=400;
R=8;
inImage=zeros(height,width);
% outImage=zeros(height,width);
% f=dir(src);
% pRange=projectRange(src);
swc(:,3:4)=swc(:,3:4)*10/3;
lineArray=readLine(swc);
lineNum=size(lineArray,1);
lineLong=zeros(lineNum,2);
for i=1:lineNum
    lineLong(i,1)=size(lineArray{i,1},1);
    lineLong(i,2)=i;
end
m=max(lineLong(:,1));
l=find(lineLong(:,1)==m);
n=size(l,1);

for j=1:n
    whichLine=lineLong(l(1,j),2);
    maxLineNum=lineLong(l(1,j),1);
    singleLineSwc=zeros(maxLineNum,7);
    xyz=zeros(1,3);
    for i=1:maxLineNum
        singleLineSwc(i,1)=i;
        singleLineSwc(i,2)=1;
        singleLineSwc(i,3:5)=round(lineArray{whichLine,1}(i,3:5));
        singleLineSwc(i,6)=1;
        if(i==1)
            singleLineSwc(i,7)=-1;
        else
            singleLineSwc(i,7)=i-1;
        end
    end
end

format long;
maxZ=max(singleLineSwc(:,5));
minZ=min(singleLineSwc(:,5));

zNum=maxZ-minZ+1;
zCollect={};

for i=1:zNum
    z=i+minZ-1;
    sameZindex=find(singleLineSwc(:,5)==z);
    zCollect{i,1}=singleLineSwc(sameZindex,3:5);
end

zCollectX={};
index=0;
for i=1:interval:zNum
    index=index+1;
    zS=i;
    tmp=[];
    if(i+interval>=zNum)
        zE=zNum;
    else
        zE=i+interval;
    end
    for j=zS:zE
        tmp=[tmp;zCollect{j,1}];
    end
    zCollectX{index,1}=tmp;
end

zCollectXnum=size(zCollectX,1);
areaZx=zeros(index,4);
for i=1:index
    xyz=zCollectX{i,1};
    maxX1=max(xyz(:,1));
    minX1=min(xyz(:,1));
    maxY1=max(xyz(:,2));
    minY1=min(xyz(:,2));
    areaZx(i,1:4)=[minX1,maxX1,minY1,maxY1];
end

maxXrange=max(areaZx(:,2)-areaZx(:,1))+1;
maxYrange=max(areaZx(:,4)-areaZx(:,3))+1;
    
everySx=round((areaZx(:,2)-areaZx(:,1))/2)+areaZx(:,1)-round(outWidth/2)+1;
everyEx=round((areaZx(:,2)-areaZx(:,1))/2)+areaZx(:,1)+round(outWidth/2);
everySy=round((areaZx(:,4)-areaZx(:,3))/2)+areaZx(:,3)-round(outHeight/2)+1;    
everyEy=round((areaZx(:,4)-areaZx(:,3))/2)+areaZx(:,3)+round(outHeight/2);        



% outImage=zeros(outHeight,outWidth,3);
% for i=1:zCollectXnum
%     outImage=zeros(outHeight,outWidth,3);
%     xyz=zCollectX{i,1};
%     l=size(xyz,1);
%     for j=1:l
%         x=xyz(j,1)-everySx(i,1)+1;
%         y=xyz(j,2)-everySy(i,1)+1;
%         outImage(y,x,:)=[1,0,0];
%     end
%     imshow(outImage);
% end

for i=1:zCollectXnum
    if(i<=84)
        continue;
    end
    tmpImage=zeros(outHeight,outWidth);
    outImage=zeros(outHeight,outWidth);
    tmpImage=uint8(tmpImage);
    outImage=uint8(outImage);
    disp(['start' num2str(i,'%05d')]);
    xyz=zCollectX{i,1};
    l=size(xyz,1);
    minZ3=min(xyz(:,3));
    maxZ3=max(xyz(:,3));
    for k=minZ3:maxZ3
        zSerial=k+100;
        if(zSerial==3895)
            continue;
        end
        zSerialStr=num2str(zSerial,'%05d');
        inImage=imread([src pre zSerialStr suf]);
        disp(['reading ' src pre zSerialStr suf]);
        tmpImage=inImage(everySy(i,1):everyEy(i,1),everySx(i,1):everyEx(i,1));
        outImage=max(outImage,tmpImage);
    end
   
    imwrite(outImage,[dst pre num2str(i,'%05d') '_raw' suf])

end