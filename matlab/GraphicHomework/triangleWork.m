clc;
clear all;

x=[3,6,4];
y=[4,2,7];
patch(x,y,[1 1 0]);


shiftX=10;
shiftY=5;
[x,y]=translationTri(x,y,shiftX,shiftY);
patch(x,y,[0 1 0]);

multiX=4;
multiY=3;
[x,y]=zoomTri(x,y,multiX,multiY);
patch(x,y,[0 0 1]);

rotateAngle=2;
[x,y]=rotateTri(x,y,rotateAngle);
patch(x,y,[1 0 0]);