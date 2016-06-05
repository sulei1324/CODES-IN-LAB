clc;
clear all;


neuro_tag = '3';
axon_src = 'W:\xhu\TDI072\transSwc_all50\3\swc1\axon\';
% 配准后得到的swc1中轴突文件的路径
den_src = 'W:\xhu\TDI072\transSwc_all50\3\swc1\den\';
raw_swc_src = 'W:\xhu\TDI072\raw_swc\3\';
% 配准后得到的swc1中树突文件的路径
raw_range = [1, 528];
% raw_range = [528 - 160 + 1, 528];          
% 所用到的标准Allen图谱的范围
raw_src = 'W:\lsu\registration\AllenAtlas.tif';
% 所用到的标准Allen图谱的路径
raw_images = zeros(320, 456, raw_range(2) - raw_range(1) + 1);
labeled_swc_dst = 'W:\xhu\TDI072\labelSwc\3\';

for i = raw_range(1) : raw_range(2)
    raw_images(:, :, i - raw_range(1) + 1) = imread(raw_src, i);
end

cell_area = [];
cell_point = [];
for i = 3 : size(dir(den_src), 1)
   t = dir(den_src);
   den_swc = load([den_src t(i, 1).name]);
   raw_swc_name = [raw_swc_src t(i, 1).name(1 : end - 6) '.swc'];
   raw_swc = load(raw_swc_name);
   cell_point = den_swc(1, 3 : 5);
   cell_point = uint8(cell_point);
   cell_area = [raw_images(cell_point(2), cell_point(1), cell_point(3))];
   cell_in_raw_swc = raw_swc(1, :);
   cell_in_raw_swc(1, 2) = cell_area;
end

project_points_in_raw_swc = [];
axon_files = dir(axon_src);
for i = 3 : size(axon_files, 1)
    swc_i = load([axon_src axon_files(i, 1).name]);
    raw_swc_name = [raw_swc_src axon_files(i, 1).name(1 : end - 6) '.swc'];
    raw_swc = load(raw_swc_name);
    swc_lines = getLines(swc_i);
    for j = 1 : size(swc_lines, 1)
       line_j = swc_lines{j};
       point_j = line_j(size(line_j, 1), 3 : 5);
       point_j = uint8(point_j);
       if point_j(1) > 455 || point_j(2) > 319 || point_j(1) < 0 || point_j(2) < 0
           continue;     
       end
       if point_j(3) > (raw_range(2) - raw_range(1)) 
           point_j(3) = (raw_range(2) - raw_range(1));
       end
       if point_j(3) < 0
           point_j(3) = 0;
       end
       project_j_area = raw_images(point_j(2) + 1, point_j(1) + 1, point_j(3) + 1);
       if project_j_area == 0
           h = 2;
           while project_j_area == 0
               project_j_area = raw_images(point_j(2) + 1, point_j(1) + 1, point_j(3) + h);
               h = h + 1;
           end    
       end
       project_j_in_raw_swc = raw_swc(line_j(size(line_j, 1), 1), :);
       project_j_in_raw_swc(1, 2) = project_j_area;
       project_points_in_raw_swc = [project_points_in_raw_swc; project_j_in_raw_swc];
    end
end

cell_in_raw_swc(1, 1) = 1;
cell_in_raw_swc(1, 7) = -1;
dlmwrite([labeled_swc_dst neuro_tag '_cell.swc'], cell_in_raw_swc, 'delimiter', ' ',  'newline','pc');

project_points_in_raw_swc = sortrows(project_points_in_raw_swc, 2);
for i = 1 : size(project_points_in_raw_swc, 1)
    cur_area = project_points_in_raw_swc(i, 2);
    if i == 1
       tmp_swc = project_points_in_raw_swc(1, :); 
       last_area = cur_area;
       continue;
    end
    if cur_area ~= last_area
        tmp_swc(:, 7) = -1;
        disp(size(tmp_swc));
        for j = 1 : size(tmp_swc)
            tmp_swc(j, 1) = j;
        end
        dlmwrite([labeled_swc_dst neuro_tag num2str(last_area) '_pro.swc'], tmp_swc, 'delimiter', ' ',  'newline','pc');
        tmp_swc = project_points_in_raw_swc(i, :);    
        last_area = cur_area;
        continue
    end
    tmp_swc = [tmp_swc; project_points_in_raw_swc(i, :)];
    last_area = project_points_in_raw_swc(i, 2);
end



