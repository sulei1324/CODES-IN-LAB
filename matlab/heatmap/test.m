clc;
clear all;

% swc = load('tree.swc');
% swc_cord = swc(:, 3 : 5);
% swc_cord = swc_cord - repmat(swc_cord(1, :), size(swc_cord, 1), 1);
% swc(:, 3 : 5) = swc_cord;
% 
% segment_cell = {};
% index = 1;
% for i = 2 : size(swc, 1)
%     p = swc(i, 7);
%     tmp_seg = [swc(p, :); swc(i, :)];
%     segment_cell{index, 1} = tmp_seg;
%     index = index + 1;
% end
% 
% total_segment_length = 0;
% 
% 
% for i = 1 : size(segment_cell, 1)
%     tmp_seg = segment_cell{i, 1};
%     x1 = tmp_seg(1, 3);
%     x2 = tmp_seg(2, 3);
%     y1 = tmp_seg(1, 4);
%     y2 = tmp_seg(2, 4);
%     total_segment_length = total_segment_length + getDistance([x1, y1], [x2, y2]);
% end
% 
% plus_grid_x = [];
% minus_grid_x = [];
% for i = 1 : size(segment_cell, 1)
%     tmp_seg = segment_cell{i, 1};
%     x1 = tmp_seg(1, 3);
%     x2 = tmp_seg(2, 3);
%     if x1 == x2
%         continue;
%     end
%     y1 = tmp_seg(1, 4);
%     y2 = tmp_seg(2, 4);
%     k = (y2 - y1) / (x2 - x1);
%     max_x = max(x1, x2);
%     min_x = min(x1, x2);
%     grid_s = floor(min_x / 10);
%     grid_e = ceil(max_x / 10);
% %     disp([x1, y1, x2, y2, grid_s, grid_e]);
%     for j = grid_s : grid_e
%         if j == grid_s
%             continue;
%         else
%             grid_1 = j - 1;
%             grid_2 = j;
%             tmp_l = 0;
%             if grid_1 * 10 < min_x && grid_2 * 10 > max_x
% %                 disp('0 intersection point.');
%                 tmp_l = getDistance([x1, y1], [x2, y2]);
%             elseif min_x * 10 < grid_1 && max_x * 10 > grid_2
% %                 disp('2 intersection point.');
%                 t_x1 = grid_1 * 10;
%                 t_y1 = k * t_x1 - k * x1 + y1;
%                 t_x2 = grid_2 * 10;
%                 t_y2 = k * t_x2 - k * x1 + y1;
%                 tmp_l = getDistance([t_x1, t_y1], [t_x2, t_y2]);
%             elseif min_x < grid_1 * 10 && max_x > grid_1 * 10 && max_x < grid_2 * 10
% %                 disp('1 intersection point.');
%                 t_x1 = x2;
%                 t_y1 = y2;
%                 t_x2 = grid_1 * 10;
%                 t_y2 = k * t_x2 - k * x1 + y1;
%                 tmp_l = getDistance([t_x1, t_y1], [t_x2, t_y2]);
%             elseif min_x > grid_1 * 10 && min_x < grid_2 * 10 && max_x > grid_2 * 10
% %                 disp('1 intersection point.');
%                 t_x1 = x1;
%                 t_y1 = y1;
%                 t_x2 = grid_2 * 10;
%                 t_y2 = k * t_x2 - k * x1 + y1;
%                 tmp_l = getDistance([t_x1, t_y1], [t_x2, t_y2]);
%             end
%             if tmp_l ~= 0
%                 if grid_2 > 0
%                     if size(plus_grid_x, 1) < grid_2
%                         plus_grid_x(grid_2, 1) = tmp_l;
%                     else
%                         plus_grid_x(grid_2, 1) = plus_grid_x(grid_2, 1) + tmp_l;
%                     end
%                 elseif grid_2 < 0
%                     tmp_grid = - grid_2;
%                     if size(minus_grid_x, 1) < tmp_grid
%                         minus_grid_x(tmp_grid, 1) = tmp_l;
%                     else
%                         minus_grid_x(tmp_grid, 1) = minus_grid_x(tmp_grid, 1) + tmp_l;
%                     end
%                 end
%             end
%         end   
%     end
% end
% 
% plus_grid_y = [];
% minus_grid_y = [];
% for i = 1 : size(segment_cell, 1)
%     tmp_seg = segment_cell{i, 1};
%     x1 = tmp_seg(1, 4);
%     x2 = tmp_seg(2, 4);
%     if x1 == x2
%         continue;
%     end
%     y1 = tmp_seg(1, 3);
%     y2 = tmp_seg(2, 3);
%     k = (y2 - y1) / (x2 - x1);
%     max_x = max(x1, x2);
%     min_x = min(x1, x2);
%     grid_s = floor(min_x / 10);
%     grid_e = ceil(max_x / 10);
% %     disp([x1, y1, x2, y2, grid_s, grid_e]);
%     for j = grid_s : grid_e
%         if j == grid_s
%             continue;
%         else
%             grid_1 = j - 1;
%             grid_2 = j;
%             tmp_l = 0;
%             if grid_1 * 10 < min_x && grid_2 * 10 > max_x
% %                 disp('0 intersection point.');
%                 tmp_l = getDistance([x1, y1], [x2, y2]);
%             elseif min_x * 10 < grid_1 && max_x * 10 > grid_2
% %                 disp('2 intersection point.');
%                 t_x1 = grid_1 * 10;
%                 t_y1 = k * t_x1 - k * x1 + y1;
%                 t_x2 = grid_2 * 10;
%                 t_y2 = k * t_x2 - k * x1 + y1;
%                 tmp_l = getDistance([t_x1, t_y1], [t_x2, t_y2]);
%             elseif min_x < grid_1 * 10 && max_x > grid_1 * 10 && max_x < grid_2 * 10
% %                 disp('1 intersection point.');
%                 t_x1 = x2;
%                 t_y1 = y2;
%                 t_x2 = grid_1 * 10;
%                 t_y2 = k * t_x2 - k * x1 + y1;
%                 tmp_l = getDistance([t_x1, t_y1], [t_x2, t_y2]);
%             elseif min_x > grid_1 * 10 && min_x < grid_2 * 10 && max_x > grid_2 * 10
% %                 disp('1 intersection point.');
%                 t_x1 = x1;
%                 t_y1 = y1;
%                 t_x2 = grid_2 * 10;
%                 t_y2 = k * t_x2 - k * x1 + y1;
%                 tmp_l = getDistance([t_x1, t_y1], [t_x2, t_y2]);
%             end
%             if tmp_l ~= 0
%                 if grid_2 > 0
%                     if size(plus_grid_y, 1) < grid_2
%                         plus_grid_y(grid_2, 1) = tmp_l;
%                     else
%                         plus_grid_y(grid_2, 1) = plus_grid_y(grid_2, 1) + tmp_l;
%                     end
%                 elseif grid_2 < 0
%                     tmp_grid = - grid_2;
%                     if size(minus_grid_y, 1) < tmp_grid
%                         minus_grid_y(tmp_grid, 1) = tmp_l;
%                     else
%                         minus_grid_y(tmp_grid, 1) = minus_grid_y(tmp_grid, 1) + tmp_l;
%                     end
%                 end
%             end
%         end   
%     end
% end
% 
% 
% grid_x = [minus_grid_x(end:-1:1); 0; plus_grid_x(:)]./ total_segment_length;
% grid_y = [minus_grid_y(end:-1:1); 0; plus_grid_y(:)]./ total_segment_length;
% 
% grid_xy = zeros(1000, 1000);
% 
% 
% for i = 1 : size(segment_cell, 1)
%     tmp_seg = segment_cell{i, 1};
%     x1 = tmp_seg(1, 3);
%     x2 = tmp_seg(2, 3);
%     y1 = tmp_seg(1, 4);
%     y2 = tmp_seg(2, 4);
%     min_x = min(x1, x2);
%     max_x = max(x1, x2);
%     min_y = min(y1, y2);
%     max_y = max(y1, y2);
%     grid_x_s = floor(min_x / 10);
%     grid_x_e = ceil(max_x / 10);    
%     grid_y_s = floor(min_y / 10);
%     grid_y_e = ceil(max_y / 10);     
%     for j = grid_x_s : grid_x_e
%         for k = grid_y_s : grid_y_e
%             tmp_d = 0;
%             if j == grid_x_s || k == grid_y_s
%                 continue;
%             else
%                 tmp_grid_x_s = j - 1;
%                 tmp_grid_x_e = j;
%                 tmp_grid_y_s = k - 1;
%                 tmp_grid_y_e = k;
%                 tmp_d = getDistanceInGrid([x1, y1], [x2, y2], [tmp_grid_x_s, tmp_grid_y_s], ...
%                     [tmp_grid_x_e, tmp_grid_y_e]);
%             end
%             if tmp_d ~= 0
%                 grid_xy(500 + tmp_grid_x_e, 500 + tmp_grid_y_e) = grid_xy(500 + tmp_grid_x_e, 500 + tmp_grid_y_e) ...
%                     + tmp_d;
%             end            
%         end
%     end
%     
%     
%     
% end
% 
% grid_xy = grid_xy / 100;
% 
% % total_density = sum(sum(grid_xy));
% % 
% % grid_xy = grid_xy / total_density;
% colormap('hot');
% imagesc(grid_xy);
% colorbar;
% imwrite(grid_xy, '1.tif');




