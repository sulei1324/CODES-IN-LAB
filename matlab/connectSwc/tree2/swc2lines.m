function lines = swc2lines(swc)

point_num = size(swc, 1);
lines = {};

for i = 1 : point_num
   if swc(i, 7) == -1 && i ~= 1
       break;
   end
   if i == 1
       line_s = swc(i, :);
       line_e = swc(i, :);
       line_data = [line_s];
   else
       if swc(i, 7) == swc(i, 1) - 1
           line_e = swc(i, :);
           line_data = [line_data; line_e];
       else
           line_t = newLine(line_s, line_e, line_data);
           lines{size(lines, 1) + 1, 1} = line_t;
           line_s = swc(swc(i, 7), :);
           line_e = swc(i, :);
           line_data = [line_s; line_e];
       end
   end
   if i == point_num
        line_t = newLine(line_s, line_e, line_data);
        lines{size(lines, 1) + 1, 1} = line_t;
   end             
end
end