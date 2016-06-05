
clc;
clear all;

x=7364;
y=5095;
z=1840;
swcName='I5_end';
swc=load(['W:\lsu\allLong\tmp\' swcName '.swc']);

m=size(swc,1);
newSWC=zeros(m,7);
for i =1:m
    newSWC(i,1)=swc(i,1);
    newSWC(i,2)=swc(i,2);
    newSWC(i,3)=swc(i,3)-x*0.3+1;
    newSWC(i,4)=swc(i,4)-y*0.3+1;
    newSWC(i,5)=swc(i,5)-z+1;
    newSWC(i,6)=swc(i,6);
    newSWC(i,7)=swc(i,7);
end

dlmwrite(['W:\lsu\allLong\tmp\' swcName '_c.swc'],newSWC,'delimiter','\t','precision',6);
