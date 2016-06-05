clc;
clear all;
tic;
swc=load('W:\lsu\allLong\tmp\I9axonWithX3used2.swc');
src='G:\sulei\13004\10um\13004_pro_10um\1\';
dst='W:\lsu\allLong\tmp\I9-30-20\';
width=23400; 
height=32200;
outWidth=1000;
outHeight=618;
zRange=[101,6100];
pre='';
suf='_prj.tif';
interval=3;
overlap=2;
R=1;
circleR=sphericalAreaInPlat(R);
pCircle=size(circleR,1);
inImage=zeros(height,width);

xyz=convertSwc(swc,zRange);

[zCollect,zInvolvedNum]=collectXyzByZ(xyz);

zCollectWithImage=assignImage(zCollect,zInvolvedNum);

zCollectWithImageX=makeX(zCollectWithImage,zInvolvedNum,interval,overlap);






zXInvolved=size(zCollectX,1);
zCollectX1=zCollectX;
for i=1:zXInvolved
    xyz1=zCollectX{i,1};
    pointNum=size(xyz1,1);
    tmp1=xyz1(1,1:7);
    dime=1;
    for j=1:pointNum
%         if(((xyz1(j,1)-referPoint(1,1))>=outWidth)||((xyz1(j,2)-referPoint(1,2))>=outHeight))
        if(j==1)
            continue;
        end
        flag1=0;
        for k=1:dime
            tmp2=tmp1(:,:,k);
            l=size(tmp2,1);
            n=0;
            for m=1:l
                if(tmp2(m,1)==0)
                    break;
                end
                n=n+1;
            end
            referPoint(1,1:7)=tmp2(n,:);
            x0=xyz1(j,3)-referPoint(1,3);
            y0=xyz1(j,4)-referPoint(1,4);
            disXY=x0*x0+y0*y0;
            if(disXY<=400)                
                tmp1(n+1,1:7,k)=xyz1(j,1:7);
                flag1=1;
                break;
            end
        end
        if(flag1==0)
            dime=dime+1;
            tmp1(1,1:7,dime)=xyz1(j,1:7);
        end
    end
    zCollectX1{i,1}=tmp1;
end

zCollectCenter={};
zCollectMax={};
zCollectMin={};
for i=1:zXInvolved
    tmpCenter=[];
    tmpMax=[];
    tmpMin=[];
    xyz2=zCollectX1{i,1};
    dimNum=size(xyz2,3);
    if(dimNum~=1)
        disp(i);
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
        maxX1=max(xyzD(:,3));
        minX1=min(xyzD(:,3));
        maxY1=max(xyzD(:,4));
        minY1=min(xyzD(:,4));
        meanX1=round((maxX1+minX1)/2);
        meanY1=round((maxY1+minY1)/2);
        tmpCenter(j,1:2)=[meanX1,meanY1];
        tmpMax(j,1:2)=[maxX1,maxY1];
        tmpMin(j,1:2)=[minX1,minY1];
    end
    zCollectCenter{i,1}=tmpCenter;
    zCollectMax{i,1}=tmpMax;
    zCollectMin{i,1}=tmpMin;
end








% for i=1:zXInvolved
%     xyz2=zCollectX{i,1};
%     dimNum=size(xyz2,3);
%     imageName=zCollectX{i,2};
%     imageNum=size(imageName,1);
%     for j=1:imageNum
%         if(i==1)       
%             imageUsed(:,:,j)=imread(imageName(j,:));
%             disp(imageName(j,:));
%         else
%             if(j~=1)
%                 imageUsed(:,:,j)=imread(imageName(j,:));
%                 disp(imageName(j,:));
%             end
%         end
%     end
%     for j=1:dimNum
%         xyzD=xyz2(:,:,j);
%         tmpPNum=size(xyzD,1);
%         for o=tmpPNum:-1:1
%             if(xyzD(o,1)==0)
%                 xyzD(o,:)=[];
%             end
%         end
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
%         for k=1:imageNum
%             if(k==1)
%                 tmpImage=imageUsed(yS:yE,xS:xE,k);
%             else
%                 tmpImage=max(tmpImage,imageUsed(yS:yE,xS:xE,k));
%             end
%         end
%         outImage=uint8(tmpImage);
%         imwrite(outImage,[dst pre num2str(i,'%05d') '-' num2str(j,'%2d') '_raw' suf]);
%         tmpImage=repmat(tmpImage,[1,1,3]);
%         for n=1:pNum
%             pointCur=xyzD(n,1:2);
%             if(pointCur(1,1)~=0)
%                 for k=1:pCircle
%                     pointCir=circleR(k,1:2);
%                     pointCop=pointCir+pointCur;
%                     thisX=pointCop(1,1)-xS+1;
%                     thisY=pointCop(1,2)-yS+1;
%                     if((thisY<1)||(thisX<1)||(thisX>outWidth)||(thisY>outHeight))
%                         continue;
%                     else    
%                         tmpImage(thisY,thisX,1)=255;
%                         tmpImage(thisY,thisX,2)=0;
%                         tmpImage(thisY,thisX,3)=0;
%                     end
%                 end
%             end
%         end
%         outImage=tmpImage;
%         imwrite(outImage,[dst pre num2str(i,'%05d') '-' num2str(j,'%2d') '_color.jpg']);    
%     end
%     imageUsed(:,:,1)=imageUsed(:,:,imageNum);
%     for j=imageNum:-1:1
%         if(j~=1)
%             imageUsed(:,:,j)=[];            
%         end
%     end    
% end
%         


    



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

    














