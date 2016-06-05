function [lengths] = countLength(lines)
line_num = size(lines, 1);
lengths = [];
for i = 1 : line_num
    line = lines{i, 1};
    l = size(line, 1);
    start_point  = line(1, :);
    length = 0;
    for j = 2 : l
        length = power((line(j, 3) - start_point(1, 3)), 2) * 100 / 3 + ...
                 power((line(j, 4) - start_point(1, 4)), 2) * 100 / 3 + ...
                 power((line(j, 5) - start_point(1, 5)), 2) + length;
    end
    lengths(i, 1) = sqrt(length);
end
    





end