clc;
clear all;

% src = 'Y:\AppData\ZSQGroup\part3\TDI21301006-1\R\montage\';
% dst = 'W:\xhu\TDI21301006\project_25um\1\';
% zRange = [9219, 9677];
% thick = 5;
% bits = 8;
% pre = 'test_';
% suf = '_mon.tif';
% 
% for i = zRange(1) : thick : zRange(2)
%     tmp_files = {};
%     for j = 0 : thick - 1
%        slice_num = i + j;
%        if j == 0
%           s = slice_num;  
%        end
%        if slice_num > zRange(2)
%            break;
%        end
%        e = slice_num;
%        image_name = [src pre num2str(slice_num, '%05d') suf];
%        tmp_files{size(tmp_files, 1) + 1, 1} = image_name;  
%     end
%     disp(tmp_files);
%     out_image = proFunction(tmp_files, bits);
%     out_image_name = [dst num2str(s, '%05d') '-' num2str(e, '%05d') '.tif'];
%     imwrite(out_image, out_image_name);
%     disp(['outing: ' out_image_name]);
%     if slice_num >= zRange(2)
%         break;
%     end
% end

