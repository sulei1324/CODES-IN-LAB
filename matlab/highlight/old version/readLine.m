function [lineSE]=readLine(Swc)
% clc;
% clear all;
% Swc=load('Y:\Public\mostzhangyalun\sulei\matlab\m\highlight\used.swc');



% plusOneLocation=find(swc(:,7)==-1);
% plusOneNum=size(plusOneLocation);

[m,n]=size(Swc);

index1=1;
for i=1:m
    if(((i==m)&&(Swc(i,7)==-1))||((Swc(i,7)==-1)&&(Swc(i+1,7)==-1)))
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



lineNum=0;

for i=1:newSwcSize
    if(newSwc(i,7)==-1)
        lineNum=lineNum+1;
        lineStart(lineNum)=i;
    else
        if(newSwc(i,7)~=i-1)
            lineNum=lineNum+1;
            lineStart(lineNum)=i;
        end
    end


end


lineSE=cell([lineNum,1]);
j=1;
tmp=[];
index=0;

for i=1:newSwcSize
    if(   i == size(newSwc, 1) ||...% ||( i < size(mySwc, 1) && mySwc(i+1,7) == -1 ) ||...
        ( i < size(newSwc, 1) && newSwc(i+1,7) ~= i ))
        tmp = [tmp; newSwc(i,:)];
        if size(tmp, 1) > 1
            index = index + 1;
            lineSE{index} = tmp;
        end
        tmp = [];
        if  ( i < size(newSwc, 1) && newSwc(i+1,7) ~= -1 )
            tmp = [newSwc(newSwc(i+1,7),:)];
        end
       
        continue; 
    end
    tmp = [tmp; newSwc(i,:)];
end

% mD=meanDistance(lineSE);







end


        