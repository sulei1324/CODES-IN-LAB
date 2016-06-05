clc;

clear all;

Swc=load('Y:\Public\mostzhangyalun\sulei\thy1\59_CROP_RESIZE\used.swc');

[m,n]=size(Swc);

lineStart=find(Swc==-1);

lineStart=lineStart-6*m;

dValue(:,1:3)=Swc(:,3:5);


% find isolate point and delete
index1=1;
for i=1:m
    if(((i==m)&(Swc(i,7)==-1))|((Swc(i,7)==-1)&(Swc(i+1,7)==-1)))
        iPoint(index1,1)=i;
        index1=index1+1;
    end
end

iPointNum=size(iPoint,1);

newSwcSize=m-iPointNum;

newSwc=zeros(newSwcSize,n);
index2=1;
for i=1:m
    judgeI=find(iPoint==i);
    if(judgeI~=0)
        continue;
    end
    newSwc(index2,:)=Swc(i,:);
    index2=index2+1;
end






l=length(lineStart);


for i=1:l-1
    for j=lineStart(i):lineStart(i+1)-2
        dValue(j,1)=newSwc(j+1,3)-newSwc(j,3);
        dValue(j,2)=newSwc(j+1,4)-newSwc(j,4);
        dValue(j,3)=newSwc(j+1,5)-newSwc(j,5);
        if(j==lineStart(i+1)-2)
            dValue(j+1,1)=0;
            dValue(j+1,2)=0;
            dValue(j+1,3)=0;
        end
    end
end

if(i==l-1)
    for j=lineStart(i+1):m-1
        dValue(j,1)=Swc(j+1,3)-Swc(j,3);
        dValue(j,2)=Swc(j+1,4)-Swc(j,4);
        dValue(j,3)=Swc(j+1,5)-Swc(j,5);
    end
    if(j==m-1)
        dValue(j+1,1)=0;
        dValue(j+1,2)=0;
        dValue(j+1,3)=0;
    end
end


meanXDistance=mean(dValue(:,1))
meanYDistance=mean(dValue(:,2))
meanZDistance=mean(dValue(:,3))

rValue(:,1)=Swc(:,6);
rValue=ceil(rValue);
maxR=max(rValue(:))
minR=min(rValue(:))


