clc;
clear all;

src = 'W:\\lsu\\TDI072\\figure\\3\\all_cell\\bouton\\z\\';
image_src = 'W:\\lsu\\TDI072\\6-5000\\';
dst = 'W:\\lsu\\TDI072\\6-5000\\1um_c\\';
bouttons = [];
delta = [4416, 3744, -6];
pre = 'test_';
suf = '_x4416_y_3744_w_15200_h_13824.tif';


for i = 1: 9
    boutton = load([src num2str(i) '.swc']);
    bouttons = [bouttons; boutton(:, 3 : 5)];
end

bouttons(:, 1) = bouttons(:, 1) * 10 / 3;
bouttons(:, 2) = bouttons(:, 2) * 10 / 3;


rou_bouttons = round(bouttons);
uni_bouttons = unique(rou_bouttons, 'rows');
sort_bouttons = sortrows(uni_bouttons, 3);

maxz = max(sort_bouttons(:, 3));
minz = min(sort_bouttons(:, 3));

z_num = 0;

for i = minz : maxz
    t_z_num = find(sort_bouttons(:, 3) == i);
    if size(t_z_num, 1) > z_num
        z_num = t_z_num;
    end
end

used_bouttons(:, 1) = sort_bouttons(:, 1) - delta(1, 1);
used_bouttons(:, 2) = sort_bouttons(:, 2) - delta(1, 2); 
used_bouttons(:, 3) = sort_bouttons(:, 3) - delta(1, 3);


ball_r = 2;
ball_cor = [];
for i = -ball_r : ball_r
    for j = -ball_r : ball_r
        if ((i)^2 + (j)^2) <= (ball_r)^2
            ball_cor = [ball_cor; [i, j]];
        end
    end
end


for i = 1 : size(used_bouttons, 1)
    c_z = used_bouttons(i, 3);
    disp(c_z);
    if i == 1
       p_z = c_z;
       image1 = imread([image_src pre num2str(p_z, '%05d') suf]);
       [height, width] = size(image1);
       image2 = repmat(image1, [1, 1, 3]);
    end
    if c_z ~= p_z
        imwrite(image2, [dst 'test_' num2str(p_z, '%05d') '_color.tif']);
        p_z = c_z;
        image1 = imread([image_src pre num2str(p_z, '%05d') suf]);
        image2 = repmat(image1, [1, 1, 3]);
    end
    c_x = used_bouttons(i, 1) + 1;
    c_y = used_bouttons(i, 2) + 1;
    for j = 1 : size(ball_cor, 1)
        u_x = c_x + ball_cor(j, 1);
        u_y = c_y + ball_cor(j, 2);
        if u_x > width
            u_x = width;
        end
        if u_y > height
            u_y = height;
        end
        if u_x < 0
            u_x = 0;
        end
        if u_y < 0
            u_y = 0;
        end            
        image2(u_y, u_x, 1) = 255;
        image2(u_y, u_x, 2) = 0;
        image2(u_y, u_x, 3) = 0;
    end 
    if i == size(used_bouttons, 1)
        imwrite(image2, [dst 'test_' num2str(p_z, '%05d') '_color.tif']);
    end
end




% for 50um
% s_s = 26;
% s_e = 26 + 50 - 1;
% image1 = imread([image_src 'test_' num2str(s_s) '-' num2str(s_e) '_stride_50.tif']);
% [height, width] = size(image1);
% image2 = repmat(image1, [1, 1, 3]);
% 
% for i = 1 : size(used_bouttons, 1)
%     c_z = used_bouttons(i, 3);
%     if ((c_z + 26) >= s_s) && ((c_z + 26) <= s_e)
%         c_x = used_bouttons(i, 1) + 1;
%         c_y = used_bouttons(i, 2) + 1;
%         for j = 1 : size(ball_cor, 1)
%             u_x = c_x + ball_cor(j, 1);
%             u_y = c_y + ball_cor(j, 2);
%             if u_x > width
%                 u_x = width;
%             end
%             if u_y > height
%                 u_y = height;
%             end
%             if u_x < 0
%                 u_x = 0;
%             end
%             if u_y < 0
%                 u_y = 0;
%             end            
%             image2(u_y, u_x, 1) = 255;
%             image2(u_y, u_x, 2) = 0;
%             image2(u_y, u_x, 3) = 0;
%         end
%     else
%         imwrite(image2, [dst 'test_' num2str(s_s) '-' num2str(s_e) '_color.tif']);
%         s_s = s_e + 1;
%         s_e = s_s + 50 - 1;
%         image1 = imread([image_src 'test_' num2str(s_s) '-' num2str(s_e) '_stride_50.tif']);
%         image2 = repmat(image1, [1, 1, 3]);
%     end
%     if i == size(used_bouttons, 1)
%         imwrite(image2, [dst 'test_' num2str(s_s) '-' num2str(s_e) '_color.tif']);
%     end
% end
