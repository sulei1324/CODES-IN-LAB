clc;
clear all;
tic;
swc=load('W:\lsu\c3_26\used.swc');
src='Y:\Archive\MBA-GF13004_preprocess\Src\100_6100\';
dst='W:\lsu\movie\book\trace\I8\3\';
width=28452;
height=21866;
outWidth=1000;
outHeight=618;
zRange=[5,4838];
pre='test_';
suf='.tif';
% interval=30;
% overlap=400;
R=1;
circleR=sphericalAreaInPlat(R);
pCircle=size(circleR,1);

inImage=zeros(height,width);
swc(:,3:4)=swc(:,3:4)*100/30;
xyz=swc(:,3:5);
xyz=round(xyz);
% xyz=unique(xyz,'rows');
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

for i=1:zInvolved

    xyz1=zCollect{i,1};
    pointNum=size(xyz1,1);
    tmp1=zeros(1,1,1);
    referPoint=xyz1(1,1:3);
    dime=1;
    dimeIndex=1;
    for j=1:pointNum
        if(((xyz1(j,1)-referPoint(1,1))>=outWidth)||((xyz1(j,2)-referPoint(1,2))>=outHeight))
            dime=dime+1;
            dimeIndex=1;
            referPoint(1,1:3)=xyz1(j,1:3);
            tmp1(dimeIndex,1:3,dime)=xyz1(j,1:3);
        else            
            tmp1(dimeIndex,1:3,dime)=xyz1(j,1:3);
            
        end
        dimeIndex=dimeIndex+1;
    end
    zCollect{i,1}=tmp1;
end

% for i=1:zInvolved
%     xyz2=zCollect{i,1};
%     dime2=size(xyz2,3);
%     z2=xyz2(1,3,1);
%     zSerial=z2+zRange(1)-1;
%     zSerialStr=num2str(zSerial,'%05d');
%     inImage=imread([src pre zSerialStr suf]);
%     disp(['reading ' src pre zSerialStr suf]);
%     for j=1:dime2
%         xyzD=xyz2(:,:,j);
%         pNum=size(xyzD,1);
%         maxX1=max(xyzD(:,1));
%         minX1=min(xyzD(:,1));
%         maxY1=max(xyzD(:,2));
%         minY1=min(xyzD(:,2));
%         meanX1=round((maxX1+minX1)/2);
%         meanY1=round((maxY1+minY1)/2);
%         xS=meanX1-round(outWidth/2)+1;
%         xE=meanX1+round(outWidth/2);
%         yS=meanY1-round(outHeight/2)+1;
%         yE=meanY1+round(outHeight/2); 
%         tmpImage=inImage(yS:yE,xS:xE);
%         outImage=uint8(tmpImage);
%         imwrite(outImage,[dst pre num2str(i,'%05d') '-' num2str(j,'%2d') '_raw' suf]);
%         tmpImage=repmat(tmpImage,[1,1,3]);
%         for n=1:pNum
%             pointCur=xyzD(n,1:2);
%             if(pointCur(1,1)~=0)
%                 for k=1:pCircle
%                     pointCir=circleR(k,1:2);
%                     pointCop=pointCir+pointCur;
%                     tmpImage(pointCop(1,2)-yS+1,pointCop(1,1)-xS+1,1)=255;
%                     tmpImage(pointCop(1,2)-yS+1,pointCop(1,1)-xS+1,2)=0;
%                     tmpImage(pointCop(1,2)-yS+1,pointCop(1,1)-xS+1,3)=0;
%                 end
%             end
%         end
%         outImage=tmpImage;
%         imwrite(outImage,[dst pre num2str(i,'%05d') '-' num2str(j,'%2d') '_color.jpg']);    
%     end
% end
        





% maxXrange=max(areaZ(:,2)-areaZ(:,1))+1;
% maxYrange=max(areaZ(:,4)-areaZ(:,3))+1;
%     
% everySx=round((areaZ(:,2)-areaZ(:,1))/2)+areaZ(:,1)-round(outWidth/2)+1;
% everyEx=round((areaZ(:,2)-areaZ(:,1))/2)+areaZ(:,1)+round(outWidth/2);
% everySy=round((areaZ(:,4)-areaZ(:,3))/2)+areaZ(:,3)-round(outHeight/2)+1;    
% everyEy=round((areaZ(:,4)-areaZ(:,3))/2)+areaZ(:,3)+round(outHeight/2);      

% for i=1:zInvolved
%     tmpImage=zeros(outHeight,outWidth);
%     outImage=zeros(outHeight,outWidth);
%     tmpImage=uint8(tmpImage);
%     outImage=uint8(outImage);
%     disp('start');
%     xyz2=zCollect{i,1};
%     pNum=size(xyz2,1);
%     z2=xyz2(1,3);
%     zSerial=z2+zRange(1)-1;
%     zSerialStr=num2str(zSerial,'%05d');
%     inImage=imread([src pre zSerialStr suf]);
%     disp(['reading ' src pre zSerialStr suf]);
%     tmpImage=inImage(everySy(i,1):everyEy(i,1),everySx(i,1):everyEx(i,1));
%     outImage=uint8(tmpImage);
%     imwrite(outImage,[dst pre num2str(i,'%05d') '_raw' suf]);
%     tmpImage=repmat(tmpImage,[1,1,3]);
%     for j=1:pNum
%         pointCur=xyz2(j,1:2);
%         for k=1:pCircle
%             pointCir=circleR(k,1:2);
%             pointCop=pointCir+pointCur;
%             tmpImage(pointCop(1,2)-everySy(i,1)+1,pointCop(1,1)-everySx(i,1)+1,1)=255;
%             tmpImage(pointCop(1,2)-everySy(i,1)+1,pointCop(1,1)-everySx(i,1)+1,2)=0;
%             tmpImage(pointCop(1,2)-everySy(i,1)+1,pointCop(1,1)-everySx(i,1)+1,3)=0;
%         end
%     end
%     outImage=tmpImage;
%     imwrite(outImage,[dst pre num2str(i,'%05d') '_color.jpg']);    
%     
% end







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

    














