function [rgbImage]=creatRGB(singleLineSwc,R,width,height)

rgbImage=zeros(height,width);
rgbImage=repmat(double((rgbImage)./255),[1,1,3]);
ball=sphericalArea(R);
lBall=size(ball,1);
m=size(singleLineSwc,1);
for i=1:m
    x=singleLineSwc(i,3);
    y=singleLineSwc(i,4);
    for j=1:lBall
        ty=y+ball(j,1);
        tx=x+ball(j,2);
        rgbImage(ty,tx,:)=[0 1 0];
    end
end


end