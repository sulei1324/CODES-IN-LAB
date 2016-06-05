function [lines] = divide2lines(swc)

swc = trimSwc(swc);
l = size(swc, 1);
lines = {};
lines_index = 1;
line = [];
for i = 1 : l
    if(swc(i, 7) == -1 || (swc(i, 7) ~= (swc(i, 1) - 1)) || i == l)
        if(i ~= 1)
            if(i == l)
                line = [line; swc(i, :)];
            end
            lines{lines_index, 1} = line;
            lines_index = lines_index + 1;
        end
        line = [swc(i, :)];
        if swc(i, 7) ~= (swc(i, 1) - 1) && swc(i, 7) ~= -1
            line = [swc(swc(i, 7), :); line];
        end
        continue;
    end
    line = [line; swc(i, :)];

end