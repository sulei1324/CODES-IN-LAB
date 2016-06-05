function [ClusteredLightArea,maxCoord,minCoord]=getLightArea(swc,R,imImf)

% clc;
% clear all;
% width=1548;
% height=2235;
% zRange=[3468,4267];
% level=zRange(2)-zRange(1)+1;
% swc=load('Y:\Public\mostzhangyalun\sulei\thy1\3468-4267\used.swc');
% R=8;


width=imImf(1,1);
height=imImf(1,2);
level=imImf(1,3);


swc(:,3:4)=swc(:,3:4)*10/3;
line=readLine(swc);
lineNum=size(line,1);
% swc(:,3)=swc(:,3)-7364+1;
% swc(:,4)=swc(:,4)-5095+1;
% swc(:,5)=swc(:,5)-1840+1;



pointNum=0;

for i=1:lineNum
    pointNum=pointNum+size(line{i,1});
end

totalLightArea=zeros(1,3);
totalPointNum=0;

for i=1:lineNum
    disp([num2str(i) ' of ' num2str(lineNum)]);
    lineI=line{i,1};
    if isempty(lineI) ~=0
        continue;
    end
    lineI=lineI(:,3:6);
    linePointNum=size(lineI,1);
    lightArea=chooseArea(lineI,R);
    chosenPointNum=size(lightArea,1);
    j=chosenPointNum+totalPointNum;
    totalLightArea(j,1:3)=0;
    for j=1:chosenPointNum
        totalPointNum=totalPointNum+1;
        x=lightArea(j,1);
        y=lightArea(j,2);
        z=lightArea(j,3);
        
        [x,y,z]=checkXYZ(x,y,z,width,height,level);
        totalLightArea(totalPointNum,1:3)=[x,y,z];
    end
end
        
totalLightArea=unique(totalLightArea,'rows');



minZ=min(totalLightArea(:,3));
maxZ=max(totalLightArea(:,3));
minX=min(totalLightArea(:,1));
maxX=max(totalLightArea(:,1));
minY=min(totalLightArea(:,2));
maxY=max(totalLightArea(:,2));
maxCoord=[maxX,maxY,maxZ];
minCoord=[minX,minY,minZ];

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