clc;
clear all;

z=[100, 4850];
src='W:\lsu\TDI072\6-5000\1um_c\';
dst='W:\lsu\TDI072\figure\3\all_cell\bouton\1um_c\';
% src='D:\sulei\';
% dst='D:\sulei\1\'
files = dir(src);
for i= 3 : size(files, 1)
    if mod(index, 10) == 0
        disp(i);
        disp(index);
        system(['copy' ' ' src 'test_' num2str(i,'%05d') '_res.tif' ' ' dst]);
    end
    index = index + 1;
end