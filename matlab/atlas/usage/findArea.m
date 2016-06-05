clc;
clear all;

axon_src = 'W:\xhu\TDI072\transSwc_all50\3\swc1\axon\';
% 配准后得到的swc1中轴突文件的路径
den_src = 'W:\xhu\TDI072\transSwc_all50\3\swc1\den\';
% 配准后得到的swc1中树突文件的路径
raw_range = [1, 528];          
% 所用到的标准Allen图谱的范围
raw_src = 'W:\lsu\registration\AllenAtlas.tif';
% 所用到的标准Allen图谱的路径
raw_images = zeros(320, 456, raw_range(2) - raw_range(1) + 1);
record_xls = 'W:\xhu\TDI072\newLabelResult\3.xlsx';
% 输出的Excel文件的路径以及名字
[MapCell, MapArray] = getMaps();
VolumeCell = load('id_v_25um3.mat');

for i = raw_range(1) : raw_range(2)
    raw_images(:, :, i - raw_range(1) + 1) = imread(raw_src, i);
end

cell_area = [];
cell_point = [];
for i = 3 : size(dir(den_src), 1)
   t = dir(den_src);
   den_swc = load([den_src t(i, 1).name]); 
   cell_point = den_swc(1, 3 : 5);
end

project_area = [];
project_point = [];
axon_files = dir(axon_src);
for i = 3 : size(axon_files, 1)
    swc_i = load([axon_src axon_files(i, 1).name]);
    swc_lines = getLines(swc_i);
    for j = 1 : size(swc_lines, 1)
       line_j = swc_lines{j};
       project_point = [project_point; line_j(size(line_j, 1), 3 : 5)];
    end 
end

cell_point = uint8(cell_point);
cell_area = [raw_images(cell_point(2), cell_point(1), cell_point(3))];

for i = 1 : size(project_point, 1)
    point_i = project_point(i, :);
    point_i = uint8(point_i);
    if point_i(1) > 455 || point_i(2) > 319 || point_i(1) < 0 || point_i(2) < 0
        continue;     
    end
    if point_i(3) > (raw_range(2) - raw_range(1)) 
        point_i(3) = (raw_range(2) - raw_range(1));
    end
    if point_i(3) < 0
        point_i(3) = 0;
    end
    tmp_area = raw_images(point_i(2) + 1, point_i(1) + 1, point_i(3) + 1);
    project_area = [project_area; raw_images(point_i(2) + 1, point_i(1) + 1, point_i(3) + 1)];
end

uni_project_area = unique(project_area, 'rows');

record_file = {};
line_i = 1;
for i = 1 : size(cell_area, 1)
    cell_area_name = MapCell{find(MapArray == cell_area(i, 1)), 2};
    record_file{line_i, 1} = ['胞体位置： ' cell_area_name];
    xlswrite(record_xls, {'胞体位置', cell_area_name}, 1, 'A1');
    line_i = line_i + 1;
end

xlswrite(record_xls, {'投射区域名称', '区域体积（立方微米）', '投射强度（区域投射终点数\总投射终点数）'}, 1, 'A3');

xls_i = 4;
for i = 1 : size(uni_project_area, 1)
   disp(i);
   xls_range = ['A' num2str(xls_i)];
   if uni_project_area(i, 1) == 0
      continue; 
   end
   a_pro_area_id = MapArray(find(MapArray(:, 1) == uni_project_area(i, 1)), 1);
   a_pro_area_name = MapCell{find(MapArray(:, 1) == uni_project_area(i, 1)), 2};
   a_pro_area_num = size(find(project_area == uni_project_area(i, 1)), 1);
   a_pro_area_volume = VolumeCell.atlas_id_v(find(VolumeCell.atlas_id_v(:, 1) == a_pro_area_id), 2);
   record_file{line_i, 1} = ['投射区域' num2str(i, '_%05d') '： ' a_pro_area_name '， 区域体积： '  num2str(a_pro_area_volume) 'um3。 ' ...
       '投射强度： ' num2str(a_pro_area_num) '\' num2str(size(project_area, 1)) '。'];
   xlswrite(record_xls, {a_pro_area_name, num2str(a_pro_area_volume), ...
       [num2str(a_pro_area_num) '\' num2str(size(project_area, 1))]}, 1, xls_range);
   xls_i = xls_i + 1;
   line_i = line_i + 1;
end










