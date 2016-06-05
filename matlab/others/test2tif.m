clc;
clear all;


src = 'I:\2';

files = dir(src);

max_i = 0;
min_i = 5;


for i = 3 : size(files, 1)
    a_txt_name = files(i, 1).name;
    a_txt = load([src '\' a_txt_name]);
    a_txt = uint8(a_txt.*5);
%     if max(max(a_txt)) > max_i
%         max_i = max(max(a_txt));
%     end
%     if min(min(a_txt)) < min_i
%         min_i = min(min(a_txt));
%     end
    str_num = num2str(i, '%05d');
    imwrite(a_txt, ['G:\sulei\tmp\1\' str_num '.tif']);
end