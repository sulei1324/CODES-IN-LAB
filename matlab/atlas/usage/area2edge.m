clc;
clear all;


a = 'W:\xhu\test\3\tmp\a\';
b = 'W:\xhu\test\3\tmp\s\';
a_dst = 'W:\xhu\test\3\tmp\a_edge\';
s_dst = 'W:\xhu\test\3\tmp\s_edge\';
n1 = 0;
n2 = 0;
for i = 1 : 528
    a_image_name = ['b_' num2str(i, '%05d') '.tif'];
    s_image_name = ['a_' num2str(i, '%05d') '.tif'];
    a_image = imread([a a_image_name]);
    s_image = imread([b s_image_name]);
    a_edge = edge(a_image, 'canny');
    s_edge = edge(s_image, 'canny');
    n1 = n1 + size(find(a_edge ~= 0), 1);
    n2 = n2 + size(find(s_edge ~= 0), 1);
%     a_edge = uint8(a_edge);
%     s_edge = uint8(s_edge);
%     a_edge(find(a_edge ~= 0)) = 255;
%     s_edge(find(s_edge ~= 0)) = 255;
%     imwrite(a_edge, [a_dst 'a_' num2str(i, '%05d') '.tif']);
%     imwrite(s_edge, [s_dst 's_' num2str(i, '%05d') '.tif']);
end