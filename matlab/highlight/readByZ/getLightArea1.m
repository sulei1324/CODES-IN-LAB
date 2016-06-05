function [ClusteredLightArea]=getLightArea1(swc,R,imImf)

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


pointNum = size(swc, 1);


totalLightArea=zeros(1,3);
totalPointNum=0;

for i=1:lineNum
    lineI=line{i,1};
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