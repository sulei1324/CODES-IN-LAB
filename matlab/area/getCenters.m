clc;
clear all;

src = 'W:\lsu\TDI072\contour-olfactory bulb\sl\crop\outline.tif';
dst = 'W:\lsu\TDI072\contour-olfactory bulb\sl\crop\test\';
centers = load('centers.mat');
outline_areas = load('outline_areas.mat');
contours_range = [0, 45];
contour_z_range = [26, 2276];
contour_inter = 50;
contour_z = contour_z_range(1) : contour_inter : contour_z_range(2);

contours_allo = [];
outline_centers_all = [];

for i = contour_z_range(1) : contour_inter : contour_z_range(2)
   if i == contour_z_range(1)
       fir = contour_z_range(1);
       las = fir + contour_inter / 2;
   else if i == contour_z_range(2)
           fir = i - contour_inter / 2 + 1;
           las = contour_z_range(2);
       else
           fir = i - contour_inter / 2 + 1;
           las = i + contour_inter / 2;
       end
   end
   contours_allo = [contours_allo; [fir, las]];   
end

as = [];
for i = 1 : size(contours_allo, 1)
    used_outline = uint8(imread(src, 'Index', i));
    used_outline_center = centers.centers(i, :);
    [height, width] = size(used_outline);
    del_w1 = used_outline_center(2);
    del_h1 = used_outline_center(1);
    this_raw_area = outline_areas.areas(i);
    if i == size(contours_allo, 1)
        next_raw_area = 0;
    else
        next_raw_area = outline_areas.areas(i + 1);
    end
    if i == 1
        pre_raw_area = this_raw_area;
    else
        pre_raw_area = outline_areas.areas(i - 1);
    end
    for j = contours_allo(i, 1) : contours_allo(i, 2)
        this_outline = uint8(zeros(height, width));
        ratio = 1;
        if j - contour_z(i) > 0
            this_area = ((next_raw_area - this_raw_area) * (j - contour_z(i)) / 50) + this_raw_area;
            ratio = sqrt(this_area / this_raw_area);
            is_raw = 0;
        else if  j - contour_z(i) < 0
                this_area = ((this_raw_area - pre_raw_area) * (50 - contour_z(i) + j) / 50) + pre_raw_area;
                ratio = sqrt(this_area / this_raw_area);
                is_raw = 0;
            else
                this_area = this_raw_area;
                is_raw = 1;
            end
        end
        if is_raw == 1
            this_center = used_outline_center;
            this_outline = used_outline;
        else
            this_outline_re = imresize(used_outline, ratio);
            [this_height, this_width] = size(this_outline_re);
            this_bw_image = im2bw(this_outline_re, 0.5);
            this_center_struct = regionprops(this_bw_image, 'centroid');
            center_x = floor(this_center_struct.Centroid(1));
            center_y = floor(this_center_struct.Centroid(2));
            this_center = [center_y, center_x];
            if ratio > 1
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
                this_outline(1 : del_y_e - del_y_s + 1, 1 : del_x_e - del_x_s + 1) = this_outline_re(del_y_s : del_y_e, del_x_s : del_x_e);
            else if ratio < 1
                    del_x_s = used_outline_center(2) - center_x;
                    del_x_e = del_x_s + this_width - 1;
                    del_y_s = used_outline_center(1) - center_y;
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
                    this_outline(del_y_s : del_y_e, del_x_s : del_x_e) = this_outline_re(1 : del_y_e - del_y_s + 1, 1 : del_x_e - del_x_s + 1);
                end
            end                                                                      
        end
        disp(j);
        disp(uint32(this_area));
        disp(size(find(this_outline ~= 0), 1))
        as = [as; this_area];
        disp(this_center);
        imwrite(this_outline, [dst num2str(j, '%05d') '.tif']);
        outline_centers_all = [outline_centers_all; this_center];
    end   
end










% for i = z_range(1) : z_range(2)
%     image = imread(src, 'Index', i + 1);
%     bw_image = im2bw(image, 0.5);
%     center = regionprops(bw_image, 'centroid');
%     center_x = floor(center.Centroid(1));
%     center_y = floor(center.Centroid(2));
%     disp(i);
%     disp([center_y, center_x]);
%     centers = [centers; [center_y, center_x]];
% end


% src = 'W:\lsu\TDI072\contour-olfactory bulb\sl\crop\generate\';
% for i = 1 : 50 :2251
%     image = imread([src num2str(i, '%05d') '.tif']);
%     bw_image = im2bw(image, 0.01);
%     center = regionprops(bw_image, 'centroid');
%     center_x = floor(center.Centroid(1));
%     center_y = floor(center.Centroid(2));
%     disp(i);
%     disp([center_y, center_x]);
%     centers = [centers; [center_y, center_x]];
% end    
