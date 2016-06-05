clc;
clear all;


lenght_xls = 'W:\xhu\TDI072\newLabelResult\3.xlsx';
% 输出的Excel文件的路径以及名字，和之前的放到同一个文件中
raw_swc_src = 'W:\xhu\TDI072\raw_swc\3';
% 原始的（beforeANTS之前的）swc文件的路径
swc1_src = 'W:\xhu\TDI072\transSwc_all50\3\swc1';
% 得到的swc1文件的路径
allen_atlas_range = [1, 528];
raw_src = 'W:\lsu\registration\AllenAtlas.tif';
% 所用到的标准Allen图谱的路径
raw_images = zeros(320, 456, allen_atlas_range(2) - allen_atlas_range(1) + 1);
VolumeCell = load('id_v_25um3.mat');
VolumeArray = VolumeCell.atlas_id_v;
[MapCell, MapArray] = getMaps();

for i = allen_atlas_range(1) : allen_atlas_range(2)
    raw_images(:, :, i - allen_atlas_range(1) + 1) = imread(raw_src, i);
end

pass_areas = [];
raw_swc_dir = dir(raw_swc_src);
lengths_in_areas = {[], []};
total_length = 0;
for i = 3 : size(raw_swc_dir, 1)
    i_raw_swc_name = raw_swc_dir(i, 1).name;
    i_raw_swc = load([raw_swc_src '\' i_raw_swc_name]);
    i_lines = getLines(i_raw_swc);
    i_swc1_name = [i_raw_swc_name(1:end - 4) '_1.swc'];
    i_swc1 = load([swc1_src '\' i_swc1_name]);
    if size(i_swc1, 1) ~= size(i_raw_swc, 1)
       disp('Fatal Error!');  
    end
    for j = 1 : size(i_swc1)
        point_j = i_swc1(j, 3 : 5);
        x_j = uint8(point_j(1));
        y_j = uint8(point_j(2));
        z_j = uint8(point_j(3));
        if x_j > 455 || y_j > 319 || x_j < 0 || y_j < 0
            continue;     
        end
        if z_j > (allen_atlas_range(2) - allen_atlas_range(1)) 
            z_j = (allen_atlas_range(2) - allen_atlas_range(1));
        end
        if z_j < 0
            z_j = 0;
        end
        j_pass_area = raw_images(y_j + 1, x_j + 1, z_j + 1);
        pass_areas = [pass_areas; j_pass_area];
        i_raw_swc(j, 2) = j_pass_area;
    end
    pass_areas = unique(pass_areas, 'rows');
    i_lengths_in_areas = zeros(size(pass_areas, 1), 1);
    i_lines = getLines(i_raw_swc); 
    for k = 1 : size(i_lines, 1)
        k_line = i_lines{k, 1};
        if size(k_line, 1) <= 1
            continue;
        end
        for l = 1 : size(k_line, 1)
            if l == 1
               p1 = k_line(l, 3 : 5);
               p1_area = k_line(l, 2);
               continue;
            end
            p2 = k_line(l, 3 : 5);
            p2_area = k_line(l, 2);
            length_p1_to_p2 = sqrt((p2(1) - p1(1)) ^ 2 + (p2(2) - p1(2)) ^ 2 + (p2(3) - p1(3)) ^ 2);
            if p1_area == p2_area
                pass_areas_index = find(pass_areas == p2_area);                
                i_lengths_in_areas(pass_areas_index, 1) = i_lengths_in_areas(pass_areas_index, 1) + length_p1_to_p2;
            else
                pass_areas_index1 = find(pass_areas == p1_area);
                pass_areas_index2 = find(pass_areas == p2_area);
                i_lengths_in_areas(pass_areas_index1, 1) = i_lengths_in_areas(pass_areas_index1, 1) + length_p1_to_p2 / 2;
                i_lengths_in_areas(pass_areas_index2, 1) = i_lengths_in_areas(pass_areas_index2, 1) + length_p1_to_p2 / 2;    
            end
            total_length = total_length + length_p1_to_p2;
            p1 = p2;
        end

    end
    for m = 1 : size(pass_areas, 1)
        pass_area = pass_areas(m, 1);
        m_area_length = i_lengths_in_areas(m, 1);
        if m_area_length == 0
           continue; 
        end
        n = find(lengths_in_areas{1} == pass_area);
        if n
            lengths_in_areas{2}(n, 1) = lengths_in_areas{2}(n, 1) + m_area_length;
        else
            lengths_in_areas{1}(size(lengths_in_areas{1}, 1) + 1, 1) = pass_area;
            lengths_in_areas{2}(size(lengths_in_areas{2}, 1) + 1, 1) = m_area_length;
        end
    end
end

xlswrite(lenght_xls, {'总长度（μm）', num2str(total_length)}, 2, 'A1');

xlswrite(lenght_xls, {'经过脑区', '在脑区中长度（μm）', '占总长度比例 '}, 2, 'A3');
xls_i = 4;
for i = 1 : size(lengths_in_areas{1}, 1)
    disp(i);
    xls_row = ['A' num2str(xls_i)];
    i_area = lengths_in_areas{1}(i, 1);
    if i_area == 0
        continue;
    end
    i_length = lengths_in_areas{2}(i, 1);
    i_area_index = find(MapArray == i_area);
    i_area_name = MapCell{i_area_index, 2};
    i_percent = i_length / total_length;
    xlswrite(lenght_xls, {i_area_name, num2str(i_length), num2str(i_percent)}, 2, xls_row);
    xls_i = xls_i + 1;
end


