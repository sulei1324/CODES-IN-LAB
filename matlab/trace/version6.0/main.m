clc;
clear all;
tic;
swc=load('W:\lsu\movie\book\trace\I5\max.swc');
src='G:\sulei\13004\10um\13004_pro_10um\1\';
dst='W:\lsu\movie\book\trace\I5\2\';
width=23400; 
height=32200;
outWidth=1000;
outHeight=618;
zRange=[101,6100];
pre='';
suf='_prj.tif';
% interval=30;
% overlap=400;
R=1;
circleR=sphericalAreaInPlat(R);
pCircle=size(circleR,1);

inImage=zeros(height,width);
swc(:,3:4)=swc(:,3:4)*10/3;
xyzRaw=swc(:,3:5);
xyzRaw=round(xyzRaw);
xyzRaw=unique(xyzRaw,'rows');
lRaw=size(xyzRaw,1);
xyz=zeros(lRaw,3);
for i=1:lRaw
    xyz(i,1:2)=xyzRaw(i,1:2);
    xyz(i,3)=xyzRaw(i,3)+zRange(1)-1;
end

l=size(xyz,1);
% format long;

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
    xyz2=zCollect{i,1};
    dime2=size(xyz2,3);
    zSerial=xyz2(1,3,1);
    if((i==1)||(zSerial>=(startZserial+10)))
        readFlag=1;
    else
        readFlag=0;        
    end
    zSerialStr=num2str(zSerial,'%05d');
    if(readFlag)
        if(zSerial==floor(zSerial/10)*10)
            startZserial=(floor(zSerial/10)-1)*10+1;
        else
            startZserial=floor(zSerial/10)*10+1;
        end
        if(((startZserial>=351)&&(startZserial<=1991))||(startZserial==2241))
            endZserial=startZserial+9;
            disp(startZserial);
        else
            endZserial=startZserial+10;
        end        
    end 
    involvedPrImNa=[src pre num2str(startZserial,'%05d') '-' num2str(endZserial,'%05d')  suf];
    zCollect{i,2}=involvedPrImNa;
end

wi=1;
while(wi<zInvolved)
    if(wi==1)
        index=1;
    end
    involvedImNum=1;
    curProName=zCollect{wi,2};
    involedProName=curProName;
    xyz30=zCollect{wi,1};
    for j=wi+1:zInvolved
       thisProName=zCollect{j,2};
       if(~strcmp(curProName,thisProName))
           curProName=thisProName;
           involvedImNum=involvedImNum+1;
           if(involvedImNum<=3)
               involedProName=[involedProName;thisProName]; 
           end
           if(involvedImNum==3)
               wi=j;
           end
       end
       if(involvedImNum<=3)          
           tmpXYZ30=zCollect{j,1};
           xyz30=[xyz30;tmpXYZ30];
        else
            break;
        end
    end
%     xyz30=unique(xyz30,'rows');
    xyz30=sortrows(xyz30);
    zCollect3x{index,1}=xyz30;
    zCollect3x{index,2}=involedProName;
    index=index+1;
    if(j==zInvolved)
        break;
    end
end



z3xInvolved=size(zCollect3x,1);

for i=1:z3xInvolved
    xyz1=zCollect3x{i,1};
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
    zCollect3x{i,1}=tmp1;
end

for i=1:z3xInvolved
    if(i<=56)
        continue;
    end
    xyz2=zCollect3x{i,1};
    dimNum=size(xyz2,3);
    imageName=zCollect3x{i,2};
    imageNum=size(imageName,1);
    for j=1:imageNum
        if(i==57)       
            imageUsed(:,:,j)=imread(imageName(j,:));
            disp(imageName(j,:));
        else
            if(j~=1)
                imageUsed(:,:,j)=imread(imageName(j,:));
                disp(imageName(j,:));
            end
        end
    end
    for j=1:dimNum
        xyzD=xyz2(:,:,j);
        tmpPNum=size(xyzD,1);
        for o=tmpPNum:-1:1
            if(xyzD(o,1)==0)
                xyzD(o,:)=[];
            end
        end
        pNum=size(xyzD,1);
        maxX1=max(xyzD(:,1));
        minX1=min(xyzD(:,1));
        maxY1=max(xyzD(:,2));
        minY1=min(xyzD(:,2));
        meanX1=round((maxX1+minX1)/2);
        meanY1=round((maxY1+minY1)/2);
        xS=meanX1-round(outWidth/2)+1;
        xE=meanX1+round(outWidth/2);
        yS=meanY1-round(outHeight/2)+1;
        yE=meanY1+round(outHeight/2); 
        disp(xE);
        disp(xS);
        disp(yS);
        disp(yE);
        for k=1:imageNum
            if(k==1)
                tmpImage=imageUsed(yS:yE,xS:xE,k);
            else
                tmpImage=max(tmpImage,imageUsed(yS:yE,xS:xE,k));
            end
        end
        outImage=uint8(tmpImage);
        imwrite(outImage,[dst pre num2str(i,'%05d') '-' num2str(j,'%2d') '_raw' suf]);
        tmpImage=repmat(tmpImage,[1,1,3]);
        for n=1:pNum
            pointCur=xyzD(n,1:2);
            if(pointCur(1,1)~=0)
                for k=1:pCircle
                    pointCir=circleR(k,1:2);
                    pointCop=pointCir+pointCur;
                    thisX=pointCop(1,1)-xS+1;
                    thisY=pointCop(1,2)-yS+1;
                    if((thisY<1)||(thisX<1)||(thisX>outWidth)||(thisY>outHeight))
                        continue;
                    else    
                        tmpImage(thisY,thisX,1)=255;
                        tmpImage(thisY,thisX,2)=0;
                        tmpImage(thisY,thisX,3)=0;
                    end
                end
            end
        end
        outImage=tmpImage;
        imwrite(outImage,[dst pre num2str(i,'%05d') '-' num2str(j,'%2d') '_color.jpg']);    
    end
    imageUsed(:,:,1)=imageUsed(:,:,imageNum);
    for j=imageNum:-1:1
        if(j~=1)
            imageUsed(:,:,j)=[];            
        end
    end    
end
        


    



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

    














