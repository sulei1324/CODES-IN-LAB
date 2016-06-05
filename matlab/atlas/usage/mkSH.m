% function s = mkSH(d, i, ns, m1, m2, m3)
% s = 0;
% sh_name = [d '\' i '_t_points.sh'];
% dd = d;
% dd = strrep(dd, '\', '\\');
% mm1 = m1;
% mm1 = strrep(mm1, '\', '\\');
% mm2 = m2;
% mm2 = strrep(mm2, '\', '\\');
% mm3 = m3;
% mm3 = strrep(mm3, '\', '\\');
% for i = 1 : size(ns, 1)
%    n = ns{i, 1};
%    csv0 = [dd '\\csv0\\' n '_0.csv'];
%    csv1 = [dd '\\csv1\\' n '_1.csv'];
%    csv2 = [dd '\\csv2\\' n '_2.csv'];
%    if i == 1
%       sh_file = fopen(sh_name, 'w'); 
%       fprintf(sh_file, 'm1=%s\r\n', mm1);
%       fprintf(sh_file, 'm2=%s\r\n', mm2);
%       fprintf(sh_file, 'm3=%s\r\n', mm3);
%       fprintf(sh_file, '\r\n');
%    end
%    first_s = ['rpoints' num2str(i) '=' csv0];
%    second_s = ['opoints1=' csv1];
%    third_s = ['opoints2=' csv2];
%    
%    fprintf(sh_file, '%s\r\n', first_s);
%    fprintf(sh_file, '%s\r\n', second_s);
%    fprintf(sh_file, '%s\r\n', third_s);
%    fprintf(sh_file, '\r\n');
%    
%    forth_s = ['antsApplyTransformsToPoints -d 3 -i $rpoints' num2str(i) ' -o $opoints1 -t [$m1, 1]'];
%    fifth_s = ['antsApplyTransformsToPoints -d 3 -i $opoints1 -o $opoints2 -t [$m2, 1] -t $m3'];
%    fprintf(sh_file, '%s\r\n', forth_s);
%    fprintf(sh_file, '%s\r\n', fifth_s);
%    fprintf(sh_file, '\r\n');   
%    
%    
%    if i == size(ns, 1)
%       fclose(sh_file); 
%    end
% end
% 
% s = 1;
% end