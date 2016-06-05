function [in_image, temp] = filter3x3(in_image, type)
[height, width] = size(in_image);
shiftBy = 0;
for y = 1:height
    [in_image, t] = filter3(in_image, width, y, height, type);
    shiftBy = shiftBy + t;
end

for x = 1:width
    [in_image, t] = filter3(in_image, height, (x - 1)*height + 1, 1, type);
    shiftBy = shiftBy + t;
end

temp = shiftBy / width / height;



end