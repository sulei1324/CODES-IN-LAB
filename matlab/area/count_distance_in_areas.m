clc;
clear all;

load lines_in_areas;        % lines_in_areas


subbed_lines_in_areas = {};
ends_in_areas = zeros(6, 1);
length_in_areas = zeros(6, 1);


for i = 1 : size(lines_in_areas, 1)
   lines_in_this_area = lines_in_areas{i, 1};
   subbed_lines_in_this_area = {};
   for j =  1 : size(lines_in_this_area, 1)
      this_line_in_this_area = lines_in_this_area{j, 1};
      sub_lines = {};
      if size(this_line_in_this_area, 1) == 0
          subbed_lines_in_this_area{size(subbed_lines_in_this_area, 1) + 1, 1} = sub_lines;
          continue;
      end      
      for k = 1 : size(this_line_in_this_area, 1)
         if k == 1
             sub_line = [];
         elseif this_line_in_this_area(k, 7) ~= this_line_in_this_area(k - 1, 1)
             sub_lines{size(sub_lines, 1) + 1, 1} = sub_line;
             sub_line = [];
         end
         sub_line = [sub_line; this_line_in_this_area(k, :)];
         if k == size(this_line_in_this_area, 1)
            sub_lines{size(sub_lines, 1) + 1, 1} = sub_line;
         end
      end
      subbed_lines_in_this_area{size(subbed_lines_in_this_area, 1) + 1, 1} = sub_lines;
   end
   subbed_lines_in_areas{size(subbed_lines_in_areas, 1) + 1, 1} = subbed_lines_in_this_area;
end


for i = 1 : size(subbed_lines_in_areas)
   subbed_lines_in_this_area = subbed_lines_in_areas{i, 1};
   subbed_lines_d = 0;
   for j = 1 : size(subbed_lines_in_this_area, 1)
      sub_lines = subbed_lines_in_this_area{j, 1};
      if size(sub_lines, 1) == 0
          continue;
      else
          for k = 1 : size(sub_lines, 1)              
            sub_line = sub_lines{k, 1};
            sub_line_d = 0;
            raw_line = lines_in_areas{i, 1}{j, 1};
            if size(raw_line, 1) == 1
                continue;
            end
            if size(sub_line, 1) == 1
                point1 = sub_line;
                location_in_raw = find(raw_line(:, 1) == point1(1, 1));
                if location_in_raw == 1
                    point1_f = point1;
                    point1_b = raw_line(location_in_raw + 1, :);
                elseif location_in_raw == size(raw_line, 1)
                    point1_f = raw_line(location_in_raw - 1, :);
                    point1_b = point1;
                    ends_in_areas(i, 1) = ends_in_areas(i, 1) + 1;
                else
                    point1_f = raw_line(location_in_raw - 1, :);
                    point1_b = raw_line(location_in_raw + 1, :);
                end
                sub_line_d = get_distance([point1_f; point1; point1_b]) / 2.0;                        
            else
                sub_line_d_in = get_distance(sub_line);
                sub_line_d_s = 0;
                sub_line_d_e = 0;
                point_s = sub_line(1, :);
                point_e = sub_line(size(sub_line, 1), :);
                location_s_in_raw = find(raw_line(:, 1) == point_s(1, 1));              
                if location_s_in_raw ~= 1
                    point_s_f = raw_line(location_s_in_raw - 1, :);
                    sub_line_d_s = get_distance([point_s_f; point_s]);
                end
                location_e_in_raw = find(raw_line(:, 1) == point_e(1, 1));
                if location_e_in_raw ~= size(raw_line, 1)
                    point_e_b = raw_line(location_e_in_raw + 1, :);
                    sub_line_d_e = get_distance([point_e; point_e_b]);
                else
                    ends_in_areas(i, 1) = ends_in_areas(i, 1) + 1;
                end                
                sub_line_d = sub_line_d_in + sub_line_d_s + sub_line_d_e;
            end
            subbed_lines_d = subbed_lines_d + sub_line_d;
                                  
          end
          
      end
   end 
   length_in_areas(i, 1) =  subbed_lines_d;
end



