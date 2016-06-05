
clc;
clear all;

x=10200;
y=13240;
z=1079;
swcName='SpatialGraph4';
swc=load(['Z:\lsu\TDI21301008\ChC Reconstrution\Cell 1\' swcName '.swc']);

m=size(swc,1);
newSwc=zeros(m,7);
for i =1:m
    newSWC(i,1)=swc(i,1);
    newSWC(i,2)=swc(i,2)+1;
    newSWC(i,3)=swc(i,3);
    newSWC(i,4)=swc(i,4);
    newSWC(i,5)=swc(i,5);
    newSWC(i,6)=swc(i,6);
    newSWC(i,7)=swc(i,7);
end

dlmwrite(['Z:\lsu\TDI21301008\ChC Reconstrution\Cell 1\' swcName 'test.swc'],newSWC,'delimiter','\t','precision',6);
