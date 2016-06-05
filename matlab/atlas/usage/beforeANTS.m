clc;
clear all;
% 待配准数据的名字
sample_id = 'TDI20to72';
% 原始图的宽和高
w = 23760;
h = 35000;
% 原始ＳＷＣ文件的路径
neuro_swcs_src = 'W:\xhu\TDI072\raw_swc\bouttons';
% 输出的路径
dst = 'W:\xhu\TDI072\transSwc_all\bouttons';
% 图谱配准后得到的三个转化矩阵的路径
mm1 = 'W:\xhu\TDI072\registration\affine0GenericAffine.mat';
mm2 = 'W:\xhu\TDI072\registration\syn0GenericAffine.mat';
mm3 = 'W:\xhu\TDI072\registration\syn1InverseWarp.nii.gz';
% 原始数据旋转方向
isTurnLeft = 1;


if mkFiles(dst) ~= 1
    disp('make files failed!');
end
neuro_names = getNames(neuro_swcs_src);
if mkSH(dst, sample_id, neuro_names, mm1, mm2, mm3) ~= 1
   disp('make sh file failed!'); 
end


shift_z = 0;
swc_dst = [dst '\swc0'];
neuro_files = dir(neuro_swcs_src);
csv0_dst = [dst '\csv0'];
for i = 3 : size(neuro_files)
   a_axon_name = neuro_files(i).name;
   a_axon_id = a_axon_name(1 : end -4);
   disp(a_axon_name);
   a_swc = load([neuro_swcs_src '\' a_axon_name]);
   a_swc(:, 5) = (a_swc(:, 5) - shift_z) / 25;
%    a_swc(:, 5) = (476 - a_swc(:, 5)) / 2.5;
   if isTurnLeft
       t_x = a_swc(:, 3);
       a_swc(:, 3) = a_swc(:, 4) / 25;
       a_swc(:, 4) = (w * 0.3 - t_x) / 25;
   else
       t_y = a_swc(:, 4);
       a_swc(:, 4) = a_swc(:, 3) / 25;
       a_swc(:, 3) = (h * 0.3 - t_y) / 25;
   end

   csv_file = [a_axon_name(1 : end - 4) '_0.csv'];
   dlmwrite([swc_dst '\0_' a_axon_name],a_swc,'delimiter',' ',  'newline','pc');
   tmp = [a_swc(:, 3 : 5)];
   a_csv = fopen([csv0_dst '\' csv_file], 'w');
   fprintf(a_csv, '%s\r\n', 'x,y,z,t');
   for j = 1 : size(tmp)
       fprintf(a_csv, '%f,%f,%f,0\r\n', tmp(j, 1), tmp(j, 2), tmp(j, 3));
   end
   fclose(a_csv);
end
% for i = 3 : size(den_files)
%    a_den_name = den_files(i).name;
%    a_den_id = a_den_name(1 : end -4);
%    disp(a_den_name);
%    a_swc = load([den_swc_src '\' a_den_name]);
%    a_swc(:, 5) = (a_swc(:, 5) - shift_z) / 25;
%    t_y = a_swc(:, 4);
%    a_swc(:, 4) = a_swc(:, 3) / 25;
%    a_swc(:, 3) = (h * 0.3 - t_y) / 25;
%    csv_file = [a_den_name(1 : end - 4) '_0.csv'];
%    dlmwrite([swc_dst '\0_' a_den_name],a_swc,'delimiter',' ',  'newline','pc');
%    tmp = [a_swc(:, 3 : 5)];
%    a_csv = fopen([csv0_dst '\' csv_file], 'w');
%    fprintf(a_csv, '%s\r\n', 'x,y,z,t');
%    for j = 1 : size(tmp)
%        fprintf(a_csv, '%f,%f,%f,0\r\n', tmp(j, 1), tmp(j, 2), tmp(j, 3));
%    end
%    fclose(a_csv);
% end




% for TDI11302020
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
%    csv_file = [a_axon_name(1 : end - 4) '_0.csv'];
%    dlmwrite([swc_dst '\0_' a_axon_name],a_swc,'delimiter',' ',  'newline','pc');
%    tmp = [a_swc(:, 3 : 5)];
%    a_csv = fopen([csv0_dst '\' csv_file], 'w');
%    fprintf(a_csv, '%s\r\n', 'x,t,z,t');
%    for j = 1 : size(tmp)
%        fprintf(a_csv, '%f,%f,%f,0\r\n', tmp(j, 1), tmp(j, 2), tmp(j, 3));
%    end
%    fclose(a_csv);
% end
% for i = 3 : size(den_files)
%    a_den_name = den_files(i).name;
%    a_den_id = a_den_name(1 : end -4);
%    disp(a_den_name);
%    a_swc = load([den_swc_src '\' a_den_name]);
%    a_swc(:, 5) = 476 - (a_swc(:, 5) - shift_z) / 10;
%    a_swc(:, 5) = a_swc(:, 5) / 2.5;
% %    a_swc(:, 5) = a_swc(:, 5) / 2.5;
%    t_y = a_swc(:, 4);
%    a_swc(:, 4) = a_swc(:, 3) / 25;
%    a_swc(:, 3) = (h * 0.3 - t_y) / 25;
%    csv_file = [a_den_name(1 : end - 4) '_0.csv'];
%    dlmwrite([swc_dst '\0_' a_den_name],a_swc,'delimiter',' ',  'newline','pc');
%    tmp = [a_swc(:, 3 : 5)];
%    a_csv = fopen([csv0_dst '\' csv_file], 'w');
%    fprintf(a_csv, '%s\r\n', 'x,t,z,t');
%    for j = 1 : size(tmp)
%        fprintf(a_csv, '%f,%f,%f,0\r\n', tmp(j, 1), tmp(j, 2), tmp(j, 3));
%    end
%    fclose(a_csv);
% end
