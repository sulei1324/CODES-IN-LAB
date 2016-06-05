function [result_cells, result_array] = getMaps()
fid = fopen('mapword.txt', 'r');

result_cells = {};
result_array = [];
i = 1;
tline = fgetl(fid);
while ischar(tline)
    tmp_cells = strsplit(tline, '\t');
    result_cells{i, 1} = str2num(tmp_cells{1}); 
    result_cells{i, 2} = tmp_cells{2}; 
    result_array(i, 1) = str2num(tmp_cells{1});
    i = i + 1;
    tline = fgetl(fid);
end

fclose(fid);

end