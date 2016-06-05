function [ClusteredLightArea]=getLightArea(swc,R,imImf)

% clc;
% clear all;
% width=1001;
% height=601;
% zRange=[0,400];
% xS = 11600;
% yS = 24000;
% zS = 3200;
% level=zRange(2)-zRange(1)+1;
% imImf=[width,height,level, xS, yS, zS];
% src=('W:\lsu\TDI072\1\axon\branch2\2-1sub\');
% dst=('W:\lsu\TDI072\1\axon\branch2\2-1hl\');
% pre='2-1block-';
% suf='.tif';
% R=1;
% swc=load('W:\lsu\TDI072\1\axon\branch2\branch2.swc');


width=imImf(1,1);
height=imImf(1,2);
level=imImf(1,3);
% xS = imImf(1,4);
% yS = imImf(1,5);
% zS = imImf(1,6);
xS = 0;
yS = 0;
zS = 0;

swc(:,3:4)=swc(:,3:4) * 10 / 3;
line=readLine(swc);
lineNum=size(line,1);




pointNum=0;

for i=1:lineNum
    pointNum=pointNum+size(line{i,1});
end

totalLightArea=zeros(1,3);
totalPointNum=0;
for i=1:lineNum
    disp([num2str(i) ' of ' num2str(lineNum)]);
    lineI=line{i,1};
    lineI=lineI(:,3:6);
    linePointNum=size(lineI,1);
    lightArea=chooseArea(lineI,R);
    chosenPointNum=size(lightArea,1);
    j=chosenPointNum+totalPointNum;
    totalLightArea(j,1:3)=0;
    for j=1:chosenPointNum
        x=lightArea(j,1) - xS + 1;
        y=lightArea(j,2) - yS + 1;
        z=lightArea(j,3) - zS;
        if(x < 1 || y < 1 || z < 0 || x > width || y > height || z > level - 1)
           continue;
        end
        totalPointNum=totalPointNum+1;
        [x,y,z]=checkXYZ(x,y,z,width,height,level);
        totalLightArea(totalPointNum,1:3)=[x,y,z];
    end
end
        
totalLightArea=unique(totalLightArea,'rows');


minZ=min(totalLightArea(:,3));
maxZ=max(totalLightArea(:,3));
disp([minZ, maxZ]);
ClusteredLightArea={};

for i=minZ:maxZ
    indexZi=find(totalLightArea(:,3)==i);
    l=size(indexZi,1);
    ziArray=zeros(l,3);
    ClusteredLightArea{i-minZ+1,1}=ziArray;
end

lightPointNum=size(totalLightArea,1);
involvedLevel=maxZ-minZ+1;
rowsOfZinCluster=zeros(involvedLevel,1);


for i=1:lightPointNum
    x=totalLightArea(i,1);
    y=totalLightArea(i,2);
    z=totalLightArea(i,3);
    rowsOfZinCluster(z-minZ+1,1)=rowsOfZinCluster(z-minZ+1,1)+1;
    ClusteredLightArea{z-minZ+1,1}(rowsOfZinCluster(z-minZ+1,1),:)=[x,y,z];
end
    
end    