function [newX,newY]=rotateTri(x,y,rotateAngle)

newY=x.*sin(rotateAngle)+y.*cos(rotateAngle);
newX=x.*cos(rotateAngle)-y.*sin(rotateAngle);


end