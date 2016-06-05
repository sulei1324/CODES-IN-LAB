clc;
clear all;

swc=load('W:\lsu\anlysis\I101\I101_x2_p-c.swc');
swc(:,7)=-1;
dlmwrite('W:\lsu\anlysis\I101\I101_x2_pc.swc',swc,'delimiter',' ', 'newline','pc')

