function [rgbImage]=creatRGB(singleLineSwc,R,rgbImage,column1,column2)


ball=sphericalArea(R);
lBall=size(ball,1);
m=size(singleLineSwc,1);
singleLineSwc=round(singleLineSwc);
singleLineSwc=singleLineSwc*10/3;
for i=1:m
    x=singleLineSwc(i,column1);
    y=singleLineSwc(i,column2);
    for j=1:lBall
        ty=y+ball(j,1);
        tx=x+ball(j,2);
        rgbImage(ty,tx,:)=[0 1 0];
    end
end




end