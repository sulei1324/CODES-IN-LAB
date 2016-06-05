clc;
clear all;
tic;
swc=load('W:\lsu\B3_21\B3_21.swc');
src='Y:\Public\mostjpliu\M193_paper\flip_data\CH1\';
dst='W:\lsu\B3_21\10\';
width=28452;
height=21866;
outWidth=1000;
outHeight=618;
zRange=[5,4838];
pre='MBA-GF14193_';
suf='_CH1.tif';
interval=10;
% overlap=400;
R=1;
circleR=sphericalAreaInPlat(R);
pCircle=size(circleR,1);

inImage=zeros(height,width);
swc(:,3:4)=swc(:,3:4)*100/32;
swc(:,5)=swc(:,5)/2;
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

wi=1;
while(wi<zInvolved)
    if(wi==1)
        index=1;
    end
    involvedImNum=1;
    xyz0=zCollect{wi,1};
    z0=xyz0(1,3);
    xyzX=xyz0;
    zs=z0;
    for j=wi+1:zInvolved
        tmpXYZ=zCollect{j,1};
        tmpZ=tmpXYZ(1,3);
        if((tmpZ-z0+1)<=interval)
            xyzX=[xyzX;tmpXYZ];
            wi=j;
        else
            break;
        end
    end
    ze=zCollect{j-1,1}(1,3);
    zSE=[zs,ze];
    zCollectX{index,1}=xyzX;
    zCollectX{index,2}=zSE;
    index=index+1;
    if(j==zInvolved)
        break;
    end    
end

    

zXInvolved=size(zCollectX,1);

zCollectX1=zCollectX;



for i=1:zXInvolved
    xyz1=zCollectX{i,1};
    pointNum=size(xyz1,1);
    tmp1=xyz1(1,1:3);
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
            referPoint(1,1:3)=tmp2(n,:);
            x0=xyz1(j,1)-referPoint(1,1);
            y0=xyz1(j,2)-referPoint(1,2);
            disXY=x0*x0+y0*y0;
            if(disXY<=400)                
                tmp1(n+1,1:3,k)=xyz1(j,1:3);
                flag1=1;
                break;
            end
        end
        if(flag1==0)
            dime=dime+1;
            tmp1(1,1:3,dime)=xyz1(j,1:3);
        end
    end
    zCollectX1{i,1}=tmp1;
end

for i=1:zXInvolved
    xyz2=zCollectX1{i,1};
    zSE=zCollectX1{i,2};
    for l=zSE(1):zSE(2)
        z0=l;
        zSerial=z0+zRange(1)-1;
        zSerialStr=num2str(zSerial,'%05d');
        tmpImage0=imread([src pre zSerialStr suf]);
        disp(['reading ' src pre zSerialStr suf]);
        if(l==zSE(1))
            usedImage=tmpImage0;
        else
            usedImage=max(usedImage,tmpImage0);
        end
    end    
    dime2=size(xyz2,3);
    for j=1:dime2
        xyzD=xyz2(:,:,j);
        pNum=size(xyzD,1);
        for o=pNum:-1:1
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
        tmpImage=usedImage(yS:yE,xS:xE);
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
end
        














