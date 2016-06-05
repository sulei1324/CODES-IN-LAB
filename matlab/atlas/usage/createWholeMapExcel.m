clc;
clear all;

[MapCell, MapArray] = getMaps();
volume_cell = load('id_v_25um3');
volume_array = volume_cell.atlas_id_v;
xls_src = 'volumes.xlsx';
xlswrite(xls_src, ['脑区名称', '脑区体积(立方微米)'], 1, 'A1');
j = 0;
k = 2;
for i = 1 : size(volume_array, 1)
    disp(i);
    xls_row = ['A' num2str(k)];
    i_area = volume_array(i, 1);
    if i_area == 0
        continue;
    end
    i_volume = volume_array(i, 2);
    i_index = find(MapArray == i_area);
    if i_index
        i_name = MapCell{i_index, 2};
%         disp(i_name);
    else
        i_name = 'Undefined';
%         disp(i_area);
        j = j + 1;
    end
    xlswrite(xls_src, {i_name, num2str(i_volume)}, 1, xls_row);
    k = k + 1;
end