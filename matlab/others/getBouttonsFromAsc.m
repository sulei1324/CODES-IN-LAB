clc;
clear all;

% asc = fopen('C:\Users\ËÕÀ×\Desktop\1.ASC', 'r');
% dst = 'C:\Users\ËÕÀ×\Desktop\1.swc';
% boutton_tag_start = '(Name "Marker 11")';
% boutton_tag_end = 'End of markers';
% start_flag = 0;
% end_flag = 0;
% index = 1;
% swc = [];
% a_line = fgetl(asc);
% index = 1;
% while ischar(a_line)
%     disp('__reading__');
%     if strfind(a_line, boutton_tag_end)
%         end_flag = 1;
%     end
%     if (start_flag == 1) && (end_flag == 0)
%         tmp_list = strsplit(a_line);
%         x = str2num((tmp_list{1, 3}));
%         y = str2num((tmp_list{1, 4}));
%         z = str2num((tmp_list{1, 5}));
%         r = str2num((tmp_list{1, 6}(1 : end - 1)));
%         if index == 1
%             f = -1;
%         else
%             f = index - 1;
%         end
%         tmp_swc = [index, 11, x, y, z, r, f];
%         swc = [swc; tmp_swc];
%         index = index + 1;
%     end
%     if strfind(a_line, boutton_tag_start)
%         start_flag = 1;
%     end    
%     a_line = fgetl(asc);
% end
% 
% fclose(asc);
% dlmwrite(dst, swc, 'delimiter', ' ', 'newline', 'pc');