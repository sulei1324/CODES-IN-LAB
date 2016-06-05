clc;
clear all;

swc=load('Y:\Public\mostzhangyalun\sulei\54_resize_bc159.swc');
swc(:,6)=1.0;



dlmwrite('Y:\Public\mostzhangyalun\sulei\54_resize_bc159_gai.swc',swc,'delimiter',' ',  'newline','pc');