function [d]=distanceXYZ(s,e)

dX=e(1)-s(1);
dY=e(2)-s(2);
dZ=e(3)-s(3);

d=dX^2+dY^2+dZ^2;
d=sqrt(d);

end