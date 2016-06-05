clc;
clear all;

a=load('Y:\Public\mostzhangyalun\sulei\thy1\temp\3-7_crop_resize135.swc');

b=round(a);

c=round(b-a);

save('Y:\Public\mostzhangyalun\sulei\thy1\temp\1.mat','b');
