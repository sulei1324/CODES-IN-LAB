clc;
clear all;
load areas;
load bouttons;     % used_bouttons
load used_lines;     %all_moved_lines


width = 10736;
height = 6000;
dst = 'W:\lsu\TDI072\contour-olfactory bulb\sl\crop\generate1\';
contour_name = {'gr'; 'ipl'; 'mi'; 'opl'; 'gl'; 'onl'};
contour_range = [[0, 45]; [2, 42]; [2, 42]; [0, 45]; [0, 43]; [0, 39]];
src = 'W:\lsu\TDI072\contour-olfactory bulb\sl\crop\';
del = [4464, 7824];
contours_range = [0, 45];
contour_z_range = [26, 2276];
contour_inter = 50;
contour_z = 26 : contour_inter : 2276;
outline_centers = load('outline_centers_all.mat');
outline_centers = outline_centers.outline_centers_all;
contour_outlines_centers = load('centers.mat');
contour_outlines_centers = contour_outlines_centers.centers;
z_allo = [];
r_a = [];
ball_r = 20;
ball_cor = [];
for i = -ball_r : ball_r
    for j = -ball_r : ball_r
        if ((i)^2 + (j)^2) <= (ball_r)^2
            ball_cor = [ball_cor; [i, j]];
        end
    end
end



for i = contour_z_range(1) : contour_inter : contour_z_range(2)
    if i == contour_z_range(1)
        s = contour_z_range(1);
        e = i + contour_inter / 2;
    else if i == contour_z_range(2)
        s = i - contour_inter / 2 + 1;
        e = contour_z_range(2);
        else
            s= i - contour_inter / 2 + 1;
            e = i + contour_inter / 2;
        end
    end
    z_allo = [z_allo; [s, e]];
end



bouttons_num_array = [];
for i = 1 : size(contour_name, 1)
    bouttons_num_array(i) = 0;
end

tmp_lines = {};
for i = 1 : size(all_moved_lines, 1)
    tmp_lines{i, 1} = [];
end




lines_in_areas = {};
for i = 1 : size(contour_name, 1)
    lines_in_areas{i, 1} = tmp_lines;
end



for i = 1 : size(z_allo, 1)
    used_raw_contours = uint8(zeros(height, width));
    used_contour_center = contour_outlines_centers(i, :);
    del_w1 = used_contour_center(2);
    del_h1 = used_contour_center(1);
    for j = 1 : size(contour_name, 1)
        if contour_range(j, 1) <= (i - 1) && (i - 1) <= contour_range(j, 2)
            contour_src = [src contour_name{j} '.tif'];
            contour_index = i - contour_range(j, 1);
            contour_image = imread(contour_src, 'Index', contour_index);
            used_raw_contours(contour_image ~= 0) = j * 40;            
        end       
    end
    this_raw_area = areas(i);
    if i == size(z_allo, 1)
        next_raw_area = 0;
    else
        next_raw_area = areas(i + 1);
    end
    if i == 1
        pre_raw_area = this_raw_area;
    else
        pre_raw_area = areas(i - 1);
    end
    for j = z_allo(i, 1) : z_allo(i, 2)
        if j - contour_z(i) > 0
            this_area = ((next_raw_area - this_raw_area) * (j - contour_z(i)) / 50) + this_raw_area;
            ratio = this_area / this_raw_area;
            is_raw = 0;
        else if  j - contour_z(i) < 0
                this_area = ((this_raw_area - pre_raw_area) * (50 - contour_z(i) + j) / 50) + pre_raw_area;
                ratio = this_area / this_raw_area;
                is_raw = 0;
            else
                this_area = this_raw_area;
                is_raw = 1;
            end
        end
        if is_raw == 1
            used_contours = used_raw_contours;
            r = 1;
        else
            r = sqrt(ratio);
            ratioed_contours = imresize(used_raw_contours, r);
            this_width = size(ratioed_contours, 2);
            this_height = size(ratioed_contours, 1);
            this_center = outline_centers(j - 26 + 1, :);
            center_x = this_center(2);
            center_y = this_center(1);
            used_contours = uint8(zeros(height, width));
            if r < 1
                del_x_s = used_contour_center(2) - center_x;
                del_x_e = del_x_s + this_width - 1;
                del_y_s = used_contour_center(1) - center_y;
                del_y_e = del_y_s + this_height - 1;
                if del_x_s < 1
                    del_x_s = 1;
                end
                if del_x_e > width
                    del_x_e = width;
                end
                if del_y_s < 1
                    del_y_s = 1;
                end
                if del_y_e > height
                    del_y_e = height;
                end
                used_contours(del_y_s : del_y_e, del_x_s : del_x_e) = ratioed_contours(1 : del_y_e - del_y_s + 1, 1 : del_x_e - del_x_s + 1);
            else if r > 1
                    del_x_s = center_x - del_w1;
                    del_x_e = del_x_s + width - 1;
                    del_y_s = center_y - del_h1;
                    del_y_e = del_y_s + height - 1;
                    if del_x_s < 1
                        del_x_s = 1;
                    end
                    if del_x_e > this_width
                        del_x_e = this_width;
                    end
                    if del_y_s < 1
                        del_y_s = 1;
                    end
                    if del_y_e > this_height
                        del_y_e = this_height;
                    end                                                
                    used_contours(1 : del_y_e - del_y_s + 1, 1 : del_x_e - del_x_s + 1) = ratioed_contours(del_y_s : del_y_e, del_x_s : del_x_e);
                end
            end
        end
        disp(j);
        image_serial = j;
        used_contours_color = repmat(used_contours, [1, 1, 3]);
        for q = 1 : size(all_moved_lines, 1)
            line1 = all_moved_lines{q, 1};
            line1_in_this_serial = find(line1(:, 5) == image_serial);
            if size(line1_in_this_serial, 1) ~= 0
               for w = 1 : size(line1_in_this_serial, 1)
                   point1 = line1(line1_in_this_serial(w), 3 : 4);
                   point1_x = point1(1);
                   point1_y = point1(2);
                   if point1_x <= 1 || point1_y <= 1
                       continue;
                   end
                   if point1_x > width || point1_y > height
                       continue;
                   end
                   for t = 1 : size(contour_name, 1)
                      if used_contours(point1_y, point1_x) == t * 40
                          lines_in_areas{t, 1}{q, 1} = [lines_in_areas{t, 1}{q, 1}; line1(line1_in_this_serial(w), :)];
                      end
                   end                                                                                                 
               end                                                         
            end            
        end
%%%%      count bouttons number;
        bouttons_in_serial = find(used_bouttons(:, 3) == image_serial);
        if size(find(bouttons_in_serial, 1) ~= 0)
            bouttons_num_in_serial = size(bouttons_in_serial, 1);
            for k = 1 : bouttons_num_in_serial
                boutton_cor = used_bouttons(bouttons_in_serial(k), :);
                boutton_x = boutton_cor(1) - del(1);
                boutton_y = boutton_cor(2) - del(2);
                if boutton_y < 1
                    boutton_y = 1;
                end
                if boutton_y > height
                    boutton_y = height;
                end
                if boutton_x < 1
                    boutton_x = 1;
                end
                if boutton_x > width
                    boutton_x = width;
                end
%                 disp([boutton_y, boutton_x]);
                for h = 1 : size(ball_cor, 1)
                    u_x = boutton_x + ball_cor(h, 1);
                    u_y = boutton_y + ball_cor(h, 2);
                    if u_x > width
                        u_x = width;
                    end
                    if u_y > height
                        u_y = height;
                    end
                    if u_x < 1
                        u_x = 1;
                    end
                    if u_y < 1
                        u_y = 1;
                    end            
                    used_contours_color(u_y, u_x, 1) = 255;
                    used_contours_color(u_y, u_x, 2) = 0;
                    used_contours_color(u_y, u_x, 3) = 0;
                end
                for l = 1 : size(contour_name, 1)
                    if used_contours(boutton_y, boutton_x) == l * 40
                        bouttons_num_array(l) = bouttons_num_array(l) + 1;
                    end
                end
%                 disp(bouttons_num_array);
            end
       end                                                
%        imwrite(used_contours, [dst num2str(j, '%05d') '_re.tif']);
       used_contours_color = imresize(used_contours_color, 0.1);
       imwrite(used_contours_color, [dst num2str(j, '%05d') '_re_c.tif']);
    end
end
    


  



% % for i = contour_range(1) : contour_range(2)
% %     contours = uint8(zeros(6000, 10736));
% %     for j = 1 : size(contour_name, 1)
% %         if contour_range(j, 1) <= i && i <= contour_range(j, 2)
% %             disp(contour_name{j});
% %             contour_src = [src contour_name{j} '.tif'];
% %             contour_index = i - contour_range(j, 1) + 1;
% %             contour_image = imread(contour_src, 'Index', contour_index);
% %             contours(find(contour_image ~= 0)) = j * 40;            
% %         end       
% %     end
% % end