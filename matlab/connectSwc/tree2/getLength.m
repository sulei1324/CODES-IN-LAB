function line_length = getLength(points)
points_num = size(points, 1);
line_length = 0;

for i = 1 : points_num
    if points_num == 1
        break;
    else
        x1 = points(i, 3);
        x2 = points(i + 1, 3);
        y1 = points(i, 4);
        y2 = points(i + 1, 4);
        z1 = points(i, 5);
        z2 = points(i + 1, 5); 
        line_length = line_length + sqrt(((0.2* (x2 - x1)) ^ 2 + (0.2 * (y2 - y1)) ^ 2 + (z2 - z1) ^ 2));
        if i + 1 == points_num
            break;
        end
    end
end
end