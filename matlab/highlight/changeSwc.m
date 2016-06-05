
clc;
clear all;
totalMin=[17803,19603,2538];

swc1=load('G:\sulei\workplace\Swc\local_dendrite.swc');


swc1(:,3:4)=swc1(:,3:4)*10/3;

swc1(:,3)=swc1(:,3)-totalMin(1,1);
swc1(:,4)=swc1(:,4)-totalMin(1,2);
swc1(:,5)=swc1(:,5)-totalMin(1,3);



swc1(:,3:4)=swc1(:,3:4)*(0.3);


dlmwrite('G:\sulei\workplace\Swc\1.swc',swc1,'delimiter',' ',  'newline','pc');