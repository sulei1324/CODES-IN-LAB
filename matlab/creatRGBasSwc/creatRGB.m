% function [rgbImage]=creatRGB(singleLineSwc,R,rgbImage,flag,width,height,zRange)
function [rgbImage]=creatRGB(singleZPoint,rgbImage,rgbColor)

m=size(singleZPoint,1);

for i=1:m
    x=singleZPoint(i,1);
    y=singleZPoint(i,2);
    z=singleZPoint(i,3);
%     rgbImage(y,x,:)=[0 1 0];
    rgbImage(y,x,:)=rgbColor;
end




end