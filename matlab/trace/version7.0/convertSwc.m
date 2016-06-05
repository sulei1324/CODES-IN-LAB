function [xyz]=convertSwc(swc,zRange)

swc(:,3:4)=swc(:,3:4)*10/3;
xyzRaw=swc(:,1:7);
xyzRaw=round(xyzRaw);
% xyzRaw=unique(xyzRaw,'rows');
lRaw=size(xyzRaw,1);
xyz=zeros(lRaw,7);
for i=1:lRaw
    xyz(i,1:4)=xyzRaw(i,1:4);
    xyz(i,5)=xyzRaw(i,5)+zRange(1)-1;
    xyz(i,6:7)=xyzRaw(i,6:7);
end