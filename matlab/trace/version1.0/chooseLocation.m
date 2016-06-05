function [w,h,X,Y]=chooseLocation(slice,width,height)
n=size(slice,1);
mArray=zeros(1,4);
% mArray column 1:max of X column 2:min of X column 3:max of Y column 4:min of Y
index=1;
for i=1:n
    if(size(slice{i,1},1)==0)
        continue;
    end
    mArray(index,1)=max(slice{i,1}(:,1));
    mArray(index,2)=min(slice{i,1}(:,1));
    mArray(index,3)=max(slice{i,1}(:,2));
    mArray(index,4)=min(slice{i,1}(:,2));
    index=index+1;
end

maxX=max(mArray(:,1));
minX=min(mArray(:,2));
maxY=max(mArray(:,3));
minY=min(mArray(:,4));


X=[minX-500,maxX+500];
Y=[minY-500,maxY+500];

[X,Y]=checkXY(X,Y,width,height);

w=X(1,2)-X(1,1)+1;
h=Y(1,2)-Y(1,1)+1;


% centerX=round(minX+width/2);
% centerY=round(minY+height/2);