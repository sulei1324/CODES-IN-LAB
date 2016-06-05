function [sphPoint]=chooseArea(line,R)
insLine=insertLine(line);
insLine=round(insLine);

insLine=insertLine(line);
insLine=round(insLine);

l=size(insLine,1);
xyz=zeros(1,3);
r=ceil(insLine(:,4));
maxR=max(r);
minR=min(r);
% R=2;


% for i=minR:maxR
%     ball{i-minR+1,1}=sphericalArea(i);
% end

iBall=sphericalArea(R);
index=1;
sphPoint=[];

nBall=size(iBall,1);
usedBall=zeros(nBall,1);
sphPoint=zeros(nBall*l,3);
tic;
for i=1:l
    x=insLine(i,1);
    y=insLine(i,2);
    z=insLine(i,3);
    r=insLine(i,4);
    xyz=[x y z];
%     usedBall(r-minR+1,1)=usedBall(r-minR+1,1)+1;
%     iBall=ball{(r-minR+1),1};
    lBall=size(iBall,1);
    
   
    for j=1:lBall
        sphPoint(index,1:3)=iBall(j,1:3)+xyz;
        index=index+1;
    end
  
end
toc;

tic;
sphPoint=unique(sphPoint,'rows');
toc;



end

    
    
    