function [d] = get_distance(swc_line)

d = 0;
if size(swc_line, 1) == 1
    return;
end
for i = 2 : size(swc_line, 1)
    pre_x = swc_line(i - 1, 3);
    pre_y = swc_line(i - 1, 4);
    pre_z = swc_line(i - 1, 5);
    this_x = swc_line(i, 3);
    this_y = swc_line(i, 4);
    this_z = swc_line(i, 5);
    d = d + sqrt((this_x - pre_x) ^ 2 + (this_y - pre_y) ^ 2 + (this_z - pre_z) ^ 2);    
end

return;
end