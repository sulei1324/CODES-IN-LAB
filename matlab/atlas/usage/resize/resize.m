clc;
clear all;


src = 'W:\xhu\TDI21301006\project_25um\1\';
dst = 'W:\xhu\TDI21301006\project_25um\res_25\';

files = dir(src);
index = 415;
for i = 61 : 152
   
   name_i = files(i, 1).name;
   if strcmp(name_i, 'Thumbs.db')
       continue;
   end
   disp(files(i, 1).name); 
   image_i = imread([src name_i]);
   out_name_i = [dst 'test_' num2str(index, '%05d') '_pro25.tif'];
   out_image_i = imresize(image_i, 0.012);
   imwrite(out_image_i, out_name_i);
   index = index + 1;
end