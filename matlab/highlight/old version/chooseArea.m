function [sphPoint]=chooseArea(line)
insLine=insertLine(line);
insLine=round(insLine);

l=size(insLine,1);
xyz=zeros(1,3);
r=ceil(insLine(:,4));
maxR=max(r);
minR=min(r);


for i=minR:maxR
    ball{i-minR+1,1}=sphericalArea(i);
end


index=1;
sphPoint=[];

for i=1:l
    x=insLine(i,1);
    y=insLine(i,2);
    z=insLine(i,3);
    r=insLine(i,4);
    xyz=[x y z];
    iBall=ball{(r-minR+1),1};
    lBall=size(iBall);
    for j=1:lBall
        sphPoint(index,1:3)=iBall(j)+xyz;
        index=index+1;
    end
end



end

    
    
    