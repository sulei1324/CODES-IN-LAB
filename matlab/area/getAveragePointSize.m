clc;
clear all;


load all_lines;
point_num = 0;
whole_line_length = 0;
line_length = 0;
for i = 1 : size(whole_lines, 1)
    line_length = 0;
    line = whole_lines{i, 1};
    point_num = point_num + size(line, 1);
    for j = 1 : size(line, 1)
        if j == 1
            pre_x = line(j, 3) * 10 / 3;
            pre_y = line(j, 4) * 10 / 3;
            pre_z = line(j, 5);
            continue;
        end
        point_x = line(j, 3) * 10 / 3;
        point_y = line(j, 4) * 10 / 3;
        point_z = line(j, 5);
        line_length = line_length + sqrt((point_x - pre_x) ^ 2 + (point_y - pre_y) ^ 2 + (point_z - pre_z) ^ 2);
    end
    disp(i);
    disp(line_length);
    disp(line_length / size(line, 1));
    whole_line_length = whole_line_length + line_length;  
end

each_point_length = whole_line_length / point_num;