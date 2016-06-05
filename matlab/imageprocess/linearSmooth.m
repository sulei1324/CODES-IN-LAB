clc;
clear all;

image = imread('2.tif');
image = double(image);
neighbor_type = 8;
smooth_type = 'max';             % max, min, aver
[height, width] = size(image);
out_image = zeros(height, width);
neighbor_matrix = zeros(3, 3, 2);
if neighbor_type == 4
    neighbor_matrix = [[0, 1]; [0, -1]; [1, 0]; [-1, 0]; [0, 0]];
else if neighbor_type == 8
        neighbor_matrix = [[0, 1]; [0, -1]; [1, 0]; [-1, 0]; [1, 1]; [-1, -1]; [-1, 1]; [1, -1]; [0, 0]];
    end
end

if strcmp(smooth_type, 'min')
    for i = 1:height
        for j = 1:width
            n = size(neighbor_matrix, 1);
            min_value = 256;
            for k = 1:n
                this_position = [i + neighbor_matrix(k,1), j + neighbor_matrix(k, 2)];
                if this_position(1) < 1 || this_position(2) < 1 || this_position(1) > height || this_position(2) > width
                    continue;
                end
                if image(this_position(1), this_position(2)) < min_value
                    min_value = image(this_position(1), this_position(2));
                end
            end
            out_image(i, j) = min_value;
        end
    end
end

if strcmp(smooth_type, 'max')
    for i = 1:height
        for j = 1:width
            n = size(neighbor_matrix, 1);
            max_value = -1;
            for k = 1:n
                this_position = [i + neighbor_matrix(k,1), j + neighbor_matrix(k, 2)];
                if this_position(1) < 1 || this_position(2) < 1 || this_position(1) > height || this_position(2) > width
                    continue;
                end
                if image(this_position(1), this_position(2)) > max_value
                    max_value = image(this_position(1), this_position(2));
                end
            end
            out_image(i, j) = max_value;
        end
    end
end

if strcmp(smooth_type, 'aver')
    for i = 1:height
        for j = 1:width
        n = size(neighbor_matrix, 1);
        t_value = 0;
        m = n;
            for k = 1:n
                this_position = [i + neighbor_matrix(k,1), j + neighbor_matrix(k, 2)];
                if this_position(1) < 1 || this_position(2) < 1 || this_position(1) > height || this_position(2) > width
                    m = m - 1;
                    continue;
                end
                t_value = t_value + image(this_position(1), this_position(2));
            end
        out_image(i, j) = t_value / m;
        end
    end 
    
  
end


out_image = uint8(out_image);
imshow(out_image);
image = uint8(image);
figure, imshow(image);