clc;
clear all;
sample_id = 'TDI11302020';
w = 21668;
h = 36400;
axon_swcs_src = 'W:\lsu\TDI11302020\all\sl\axon';
den_swc_src = 'W:\lsu\TDI11302020\all\sl\den';
dst = 'W:\lsu\registration\TDI11302020\swcTrans';
sh_name = [dst '\\' sample_id '_t_points.sh'];
swc0_dst = [dst '\\' 'swc0'];
csv0_dst = [dst '\\' 'csv0'];
swc1_dst = [dst '\\' 'swc1'];
csv1_dst = [dst '\\' 'csv1'];
csv2_dst = [dst '\\' 'csv2'];
if ~exist(swc0_dst, 'dir')
    mkdir(swc0_dst);
end
if ~exist(swc1_dst, 'dir')
    mkdir(swc1_dst);
end
if ~exist(csv0_dst, 'dir')
    mkdir(csv0_dst);
end
if ~exist(csv1_dst, 'dir')
    mkdir(csv1_dst);
end
if ~exist(csv2_dst, 'dir')
    mkdir(csv2_dst);
end

axon_files = dir(axon_swcs_src);
den_files = dir(den_swc_src);
neuro_names = {};
for i = 3 : size(axon_files, 1)
   axon_name = axon_files(i, 1).name(1 : end - 4); 
   neuro_names{size(neuro_names, 1) + 1, 1} = axon_name;
end
for i = 3 : size(den_files, 1)
   den_name = den_files(i, 1).name(1 : end - 4);
   neuro_names{size(neuro_names, 1) + 1, 1} = den_name; 
end
















% shift_z = 95;
% 
% for i = 3 : size(axon_files)
%    a_axon_name = axon_files(i).name;
%    a_axon_id = a_axon_name(1 : end -4);
%    disp(a_axon_name);
%    a_swc = load([axon_swcs_src '\' a_axon_name]);
%    a_swc(:, 5) = 476 - (a_swc(:, 5) - shift_z) / 10;
%    a_swc(:, 5) = a_swc(:, 5) / 2.5;
% %    a_swc(:, 5) = a_swc(:, 5) / 2.5;
%    t_y = a_swc(:, 4);
%    a_swc(:, 4) = a_swc(:, 3) / 25;
%    a_swc(:, 3) = (h * 0.3 - t_y) / 25;
%    csv_file = [a_axon_name(1 : end - 4) '.csv'];
%    dlmwrite([swc_dst '\0_' a_axon_name],a_swc,'delimiter',' ',  'newline','pc');
%    tmp = [a_swc(:, 3 : 5)];
%    a_csv = fopen([csv_dst '\' csv_file], 'w');
%    fprintf(a_csv, '%s\r\n', 'x,t,z,t');
%    for j = 1 : size(tmp)
%        fprintf(a_csv, '%f,%f,%f,0\r\n', tmp(j, 1), tmp(j, 2), tmp(j, 3));
%    end
%    fclose(a_csv);
% end
