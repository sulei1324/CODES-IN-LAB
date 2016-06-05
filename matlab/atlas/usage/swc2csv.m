clc;
clear all;

swc_src = 'W:\xhu\TDI072\transSwc_all\bouttons\swc1\';
csv_dst = 'W:\xhu\TDI072\transSwc_all50\bouttons\csv0\';


swc_files = dir(swc_src);
for i = 3 : size(swc_files, 1)
    swc_file = swc_files(i, 1).name;
    swc_name = swc_file(1 : end - 6);
    swc_i = load([swc_src swc_file]);
    csv_file = [csv_dst swc_name '_0.csv'];
    f = fopen(csv_file, 'w');
    fprintf(f, 'x,y,z,t\r\n');
    for i = 1 : size(swc_i, 1)
        line_i = swc_i(i, 3 : 5);
        fprintf(f, '%f,%f,%f,0\r\n', line_i(1), line_i(2), line_i(3));   
    end
    fclose(f);
end