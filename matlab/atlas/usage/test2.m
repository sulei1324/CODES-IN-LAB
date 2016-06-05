clc;
clear all;

fid = fopen('mapword.txt', 'r');

result_cells = {};
result_array = [];
i = 1;
tline = fgetl(fid);
while ischar(tline)
    disp(tline);
    t_index = regexp(tline, '\t');
    pixel_value = str2num(tline(1 : t_index - 1));
    area_name = tline(t_index + 1 : end);
    result_cells{i, 1} = pixel_value;
    result_cells{i, 2} = area_name;
    tline = fgetl(fid);
    i = i + 1;
end

fclose(fid);