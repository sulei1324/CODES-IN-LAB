clc;
clear all;

id = 'test1';
swc_src = 'W:\xhu\TDI072\transSwc_all\bouttons\swc1';
dst = 'W:\xhu\TDI072\transSwc_all50\bouttons';

neuro_names = getNames(swc_src);
m1 = 'W:\xhu\TDI072\res50\test30InverseWarp.nii.gz';

sh_name = [dst '\' id '_t_points.sh'];
dd = strrep(dst, '\', '\\');
mm1 = m1;
mm1 = strrep(mm1, '\', '\\');
for i = 1 : size(neuro_names, 1)
   n = neuro_names{i, 1}(1 : end - 2);
   csv0 = [dd '\\csv0\\' n '_0.csv'];
   csv1 = [dd '\\csv1\\' n '_1.csv'];
   if i == 1
      sh_file = fopen(sh_name, 'w'); 
      fprintf(sh_file, 'm1=%s\r\n', mm1);
      fprintf(sh_file, '\r\n');
   end
   first_s = ['rpoints=' csv0];
   second_s = ['opoints=' csv1];
   fprintf(sh_file, '%s\r\n', first_s);
   fprintf(sh_file, '%s\r\n', second_s);
   fprintf(sh_file, '\r\n');
   third_s = ['antsApplyTransformsToPoints -d 3 -i $rpoints -o $opoints -t $m1'];
   fprintf(sh_file, '%s\r\n', third_s);
   fprintf(sh_file, '\r\n');   
end

fclose(sh_file);
