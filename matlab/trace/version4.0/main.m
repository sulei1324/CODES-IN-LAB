clc;
clear all;
tic;
swc=load('W:\lsu\movie\book\trace\I5\max.swc');
src='Y:\Archive\MBA-GF13004_preprocess\Src\100_6100\';
dst='W:\lsu\movie\book\trace\I5\1\';
width=23400;
height=32200;
outWidth=1000;
outHeight=618;
zRange=[101,6100];
pre='test_';
suf='.tif';
% interval=30;
% overlap=400;
R=1;
circleR=sphericalAreaInPlat(R);
pCircle=size(circleR,1);

inImage=zeros(height,width);
swc(:,3:4)=swc(:,3:4)*10/3;
xyz=swc(:,3:5);
xyz=round(xyz);
xyz=unique(xyz,'rows');
l=size(xyz,1);
format long;

maxZ=max(xyz(:,3));
minZ=min(xyz(:,3));

zNum=maxZ-minZ+1;
zCollect={};
zIndex=1;
for i=1:zNum
    z=i+minZ-1;
    sameZindex=find(xyz(:,3)==z);
    if(size(sameZindex)~=0)
        zCollect{zIndex,1}=xyz(sameZindex,1:3);
        zIndex=zIndex+1;
    end
end

zInvolved=size(zCollect,1);
areaZ=zeros(zInvolved,4);
for i=1:zInvolved
    xyz1=zCollect{i,1};
    maxX1=max(xyz1(:,1));
    minX1=min(xyz1(:,1));
    maxY1=max(xyz1(:,2));
    minY1=min(xyz1(:,2));
    areaZ(i,1:4)=[minX1,maxX1,minY1,maxY1];
end

maxXrange=max(areaZ(:,2)-areaZ(:,1))+1;
maxYrange=max(areaZ(:,4)-areaZ(:,3))+1;
    
everySx=round((areaZ(:,2)-areaZ(:,1))/2)+areaZ(:,1)-round(outWidth/2)+1;
everyEx=round((areaZ(:,2)-areaZ(:,1))/2)+areaZ(:,1)+round(outWidth/2);
everySy=round((areaZ(:,4)-areaZ(:,3))/2)+areaZ(:,3)-round(outHeight/2)+1;    
everyEy=round((areaZ(:,4)-areaZ(:,3))/2)+areaZ(:,3)+round(outHeight/2);      

for i=1:zInvolved
    tmpImage=zeros(outHeight,outWidth);
    outImage=zeros(outHeight,outWidth);
    tmpImage=uint8(tmpImage);
    outImage=uint8(outImage);
    disp('start');
    xyz2=zCollect{i,1};
    pNum=size(xyz2,1);
    z2=xyz2(1,3);
    zSerial=z2+zRange(1)-1;
    zSerialStr=num2str(zSerial,'%05d');
    inImage=imread([src pre zSerialStr suf]);
    disp(['reading ' src pre zSerialStr suf]);
    tmpImage=inImage(everySy(i,1):everyEy(i,1),everySx(i,1):everyEx(i,1));
    outImage=uint8(tmpImage);
    imwrite(outImage,[dst pre num2str(i,'%05d') '_raw' suf]);
    tmpImage=repmat(tmpImage,[1,1,3]);
    for j=1:pNum
        pointCur=xyz2(j,1:2);
        for k=1:pCircle
            pointCir=circleR(k,1:2);
            pointCop=pointCir+pointCur;
            tmpImage(pointCop(1,2)-everySy(i,1)+1,pointCop(1,1)-everySx(i,1)+1,1)=255;
            tmpImage(pointCop(1,2)-everySy(i,1)+1,pointCop(1,1)-everySx(i,1)+1,2)=0;
            tmpImage(pointCop(1,2)-everySy(i,1)+1,pointCop(1,1)-everySx(i,1)+1,3)=0;
        end
    end
    outImage=tmpImage;
    imwrite(outImage,[dst pre num2str(i,'%05d') '_color.jpg']);    
    
end







% zCollectX={};
% index=0;
% for i=1:interval:zNum
%     index=index+1;
%     zS=i;
%     tmp=[];
%     if(i+interval>=zNum)
%         zE=zNum;
%     else
%         zE=i+interval;
%     end
%     for j=zS:zE
%         tmp=[tmp;zCollect{j,1}];
%     end
%     zCollectX{index,1}=tmp;
% end
% 

% 
% 

    














