clc;
clear all;
% 
% z=[100, 4850];
% src='W:\lsu\TDI072\6-5000\1um_c\';
% dst='W:\lsu\TDI072\figure\3\all_cell\bouton\1um_c\';
% % src='D:\sulei\';
% % dst='D:\sulei\1\'
% files = dir(src);
% for i= 3 : size(files, 1)
%     name_i = files(i, 1).name;
%     disp(name_i);
%     if strcmp(name_i, 'Thumbs.db')
%         continue;
%     end
%     new_name_i = [name_i(1 : end - 10) '_c.tif'];
%     image_i = imread([src name_i]);
%     disp(new_name_i);
%     imwrite(image_i, [dst new_name_i]);
% end