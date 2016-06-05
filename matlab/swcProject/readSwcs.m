clc;
clear all;

green_src = 'Z:\AppData\TDI\part3\TDI11302020\green\montage\';
red_src = 'W:\lsu\TDI11302020\red\montage\';
dst = 'W:\lsu\TDI11302020\all\terminals\';
mostd_delta = 28;
width = 21168;
height = 36400;
ball = sphericalAreaInPlat(3);

swc_files = {'W:\lsu\TDI11302020\all\jy\axon', ...
             'W:\lsu\TDI11302020\all\lyr\axon', ...
             'W:\lsu\TDI11302020\all\sl\axon', ...
             'W:\lsu\TDI11302020\all\zhm2.22\axon'};

all_swc = [];         
for i = 1 : size(swc_files, 2)
   swc_file = swc_files{1, i};
%    disp(swc_file);
   swc_in_file = dir(swc_file); 
   for j = 3 : size(swc_in_file, 1)
%        disp(swc_in_file(j).name);
       tmp_swc = load([swc_file '\' swc_in_file(j).name]);
       ts = getTerminals(tmp_swc);
       ts(:, 2) = i;
       all_swc = [all_swc; ts];
   end
end

all_swc(:, 5) = round(all_swc(:, 5));
all_sorted_swc = sortrows(all_swc, 5);

max_z = max(all_sorted_swc(:, 5));
min_z = min(all_sorted_swc(:, 5));
pro_order = [];
for i = min_z : 100 : max_z
    s = i;
    e = i + 99;
    if e > max_z
        e = max_z;
    end
    pro_order = [pro_order; s, e];
end

% index = 1;
% 
% for z_i = min_z : max_z
%    tic;
%    disp([min_z, z_i, max_z]);
%    if z_i == min_z
%        pro_count = 0;
% %        out_green_image = uint16(zeros(height, width));
%        out_red_image = uint8(zeros(height, width));
%        out_red_image = imresize(out_red_image, 0.3);
%    end
%    z_serial = z_i + 28;
%    z_str = num2str(z_serial, '%05d');
% %    disp(z_str);
% %    green_name = [green_src 'test_' z_str '_mon.tif'];
%    red_name = [red_src 'test_' z_str '_mon.tif'];
% %    tmp_green_image = imread(green_name);
%    tmp_red_image = imread(red_name);
%    tmp_red_image = imresize(tmp_red_image, 0.3);
% %    out_green_image = max(out_green_image, tmp_green_image);
%    out_red_image = max(out_red_image, tmp_red_image);
%    pro_count = pro_count + 1;
%    if pro_count == 100 || z_i == max_z
% %        out_green_image = repmat(out_green_image, [1, 1, 3]);
%        out_red_image = repmat(out_red_image, [1, 1, 3]);
%        z_s = pro_order(index, 1);
%        z_e = pro_order(index, 2);
% %        disp([z_s, z_e]);
%        for s_i = 1 : size(all_sorted_swc, 1)
%            swc_i = all_sorted_swc(s_i, :);
%            s_z = all_sorted_swc(s_i, 5);
%            if s_z >= z_s && s_z <= z_e
% %                disp(s_z);
%                if swc_i(1, 2) == 1
%                    color = [255, 0, 0];
%                elseif swc_i(1, 2) == 2
%                    color = [0, 255, 0];
%                elseif swc_i(1, 2) == 3
%                    color = [255, 255, 0];
%                elseif swc_i(1, 2) == 4
%                    color = [255, 0, 255];
%                end
%                s_x = floor(all_sorted_swc(s_i, 3));
%                s_y = floor(all_sorted_swc(s_i, 4));
%                for k = 1 : size(ball, 1)  
%                    t_x = s_x + ball(k, 1);
%                    t_y = s_y + ball(k, 2);
% %                    out_green_image(t_y, t_x, 1) = color(1);
% %                    out_green_image(t_y, t_x, 2) = color(2);
% %                    out_green_image(t_y, t_x, 3) = color(3);
%                    out_red_image(t_y, t_x, 1) = color(1);
%                    out_red_image(t_y, t_x, 2) = color(2);
%                    out_red_image(t_y, t_x, 3) = color(3);
%                end
%            end
%        end
% %        imwrite(out_green_image, [dst 'green_' num2str(index, '%02d') '.tif']);
%        imwrite(out_red_image, [dst 'red_' num2str(index, '%02d') '.tif']);
%        index = index + 1;
%        pro_count = 0;
% %        out_green_image = uint16(zeros(height, width));
%        out_red_image = uint8(zeros(height, width));
%        out_red_image = imresize(out_red_image, 0.3);
%    end
%    toc;
% end










