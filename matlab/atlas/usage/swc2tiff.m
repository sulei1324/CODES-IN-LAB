clc;
clear all;


a = load('W:\xhu\test\72_2\syn_diff.swc');
dst = zeros(320, 456, 528);

for i = 1 : size(a, 1)
   xyz = a(i, 3 : 5);
   disp(xyz);
   x = uint16(xyz(1));
   y = uint16(xyz(2));
   z = uint16(xyz(3));
   dst(y, x, z) = 1;
end

for i = 1 : size(dst, 3)
    disp(i);
    imwrite(dst(:, : , i), ['W:\xhu\test\b\' num2str(i, '%05d') '.tif']);
end