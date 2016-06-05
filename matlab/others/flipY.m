clc;
clear all;

swc=load('W:\lsu\134\00174\001743.swc');
width=100;
height=100;

newSwc=swc;
newSwc(:,4)=1+height-swc(:,4);


dlmwrite('W:\lsu\134\00174\001743_1.swc',newSwc,'delimiter',' ',  'newline','pc')
    