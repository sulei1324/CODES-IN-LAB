clc;
clear all;

f = fopen('C:\Users\куюв\Desktop\test_02290_uint8.tif', 'r');
v = fseek(f, 44398134, -1);
n = fread(f, 2);
% nOfArr = dec2base(fread(f, 2), 16);
% n = [];
% for i = 1:size(nOfArr, 1)
%     disp(nOfArr(i, 1));
%     n = [n nOfArr(i, 1)];
% end
arr = {};
% m = base2dec(n, 16);
for i = 1:11
    arr{1, i} = dec2base(fread(f, 12), 16);
end





