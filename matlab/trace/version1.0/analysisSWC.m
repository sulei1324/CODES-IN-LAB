clc;

clear all;

Swc=load('Y:\Public\mostzhangyalun\sulei\thy1\59_CROP_RESIZE\used.swc');

[m,n]=size(Swc);

lineStart=find(Swc==-1);

lineStart=lineStart-6*m;

dValue(:,1:3)=Swc(:,3:5);


l=length(lineStart);

for i=1:l-1
    for j=lineStart(i):lineStart(i+1)-2
        dValue(j,1)=Swc(j+1,3)-Swc(j,3);
        dValue(j,2)=Swc(j+1,4)-Swc(j,4);
        dValue(j,3)=Swc(j+1,5)-Swc(j,5);
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

[max,location]=max(dValue);
% 
% rValue(:,1)=Swc(:,6);
% rValue=ceil(rValue);
% a=max(rValue(:))
% b=min(rValue(:))


