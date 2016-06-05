function [zCollect,zInvolvedNum] = collectXyzByZ( xyz )

l=size(xyz,1);


maxZ=max(xyz(:,5));
minZ=min(xyz(:,5));

zNum=maxZ-minZ+1;
zCollect={};
zIndex=1;
for i=1:zNum
    z=i+minZ-1;
    sameZindex=find(xyz(:,5)==z);
    if(size(sameZindex)~=0)
        zCollect{zIndex,1}=xyz(sameZindex,1:7);
        zIndex=zIndex+1;
    end
end

zInvolvedNum=size(zCollect,1);

end

