clc;
clear all;

src = 'G:\sulei\area\I2\swc\';
width = 21168;
height = 36400;
in_image_src = 'G:\sulei\area\I2\test_3011-3030_stride_20-tag.tif';
in_image = imread(in_image_src);
cell_z_location = 2919;
files = dir(src);
n = size(files, 1);
ball = sphericalAreaInPlat(3);
out_image=repmat(in_image,[1,1,3]);


for i = 3 : n
   swc_name = [src files(i, 1).name];
   disp(swc_name);
   tmp_swc = load(swc_name);
   l = size(tmp_swc, 1);
   for j = 1 : l
       t_z = tmp_swc(j, 5);
       if t_z > cell_z_location - 100 && t_z < cell_z_location + 100
           x = tmp_swc(j, 3);
           y = tmp_swc(j, 4);
           x = floor(x);
           y = floor(y);
           for k = 1 : size(ball, 1)
               t_x = x + ball(k, 1);
               t_y = y + ball(k, 2);
               out_image(t_y, t_x, 1) = 255;
               out_image(t_y, t_x, 2) = 0;
               out_image(t_y, t_x, 3) = 0;
           end
       end
   end
end

imwrite(out_image, 'G:\sulei\area\I2\I2.jpg');