clear all;
clc;

src = 'Y:\rguo\TDI11107004\resample\222';
dst = 'Y:\rguo\TDI11107004\resample\222-8';
file1 = dir(src);
l = size(file1, 1);

for i = 3 : l
    tmp_file_name = file1(i).name;
    if strcmp(tmp_file_name, 'Thumbs.db')
        continue;
    end
    serials = tmp_file_name(1, 6 : 16);
    disp(tmp_file_name);
    tmp_image = imread([src '\' tmp_file_name]);
    tmp_image = double(tmp_image);
    tmp_image2 = tmp_image / 4095 * 255;
    tmp_image2 = uint8(tmp_image2);
    imwrite(tmp_image2, [dst '\test_' serials '.tif' ]);
    disp([dst '\test_' serials '.tif' ]);
end




% 
% a = imread('C:\Users\куюв\Desktop\test_03528-03627_pro.tif');
% 
% a = double(a);
% 
% b = a / 4095 * 255;
% 
% b = uint8(b);
% 
% imwrite(b, 'C:\Users\куюв\Desktop\1.tif');





