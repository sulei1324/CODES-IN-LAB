function d = getDistanceInGrid(p1, p2, grid_lt, grid_rb)


d = 0;
grid_x_s = grid_lt(1, 1) * 10;
grid_x_e = grid_rb(1, 1) * 10;
grid_y_s = grid_lt(1, 2) * 10;
grid_y_e = grid_rb(1, 2) * 10;

x1 = p1(1, 1);
y1 = p1(1, 2);
x2 = p2(1, 1);
y2 = p2(1, 2);
min_x = min(x1, x2);
max_x = max(x1, x2);
min_y = min(y1, y2);
max_y = max(y1, y2);

if x1 == x2
    if min_y > grid_y_s && max_y < grid_y_e
        d = abs((y2 - y1));
    elseif min_y > grid_y_s && min_y <grid_y_e && max_y > grid_y_e
        d = grid_y_e - min_y;
    elseif min_y < grid_y_s && max_y < grid_y_e && max_y > grid_y_s
        d = max_y - grid_y_s;
    end
elseif y1 == y2
    if min_x > grid_x_s && max_x < grid_x_e
        d = abs((x2 - x1));
    elseif min_x > grid_x_s && min_x <grid_x_e && max_x > grid_x_e
        d = grid_x_e - min_x;
    elseif min_x < grid_x_s && max_x < grid_x_e && max_x > grid_x_s
        d = max_x - grid_x_s;
    end
else
    k1 = (y2 - y1) / (x2 - x1);
    k2 = (x2 - x1) / (y2 - y1);
    tmp_x1 = grid_x_s;
    tmp_y1 = k1 * tmp_x1 - k1 * x1 + y1;
    tmp_x2 = grid_x_e;
    tmp_y2 = k1 * tmp_x2 - k1 * x1 + y1;
    tmp_y3 = grid_y_s;
    tmp_x3 = k2 * tmp_y3 - k2 * y1 + x1;
    tmp_y4 = grid_y_e;
    tmp_x4 = k2 * tmp_y4 - k2 * y1 + x1;
    tmp_inter = [tmp_x1, tmp_y1; tmp_x2, tmp_y2; tmp_x3, tmp_y3; tmp_x4, tmp_y4];
    right_inter = [];
    n = 0;
    for i = 1 : 4
        if tmp_inter(i, 1) < min_x || tmp_inter(i, 1) > max_x
            continue;
        else
            n = n + 1;
            right_inter(n, :) = tmp_inter(i, :);
        end
    end
    if n == 2
        d = getDistance(right_inter(1, :), right_inter(2, :));
    elseif n == 0
        if x1 > grid_x_s && x1 < grid_x_e && y1 >grid_y_s && y1 < grid_y_e ...
                && x2 > grid_x_s && x2 < grid_x_e && y2 >grid_y_s && y2 < grid_y_e
            d = getDistance([x1, y1], [x2, y2]);
        else
            d = 0;
        end
    elseif n == 1
        if x1 > grid_x_s && x1 < grid_x_e && y1 >grid_y_s && y1 < grid_y_e
            d = getDistance([x1, y1], right_inter(1, :));
        elseif x2 > grid_x_s && x2 < grid_x_e && y2 >grid_y_s && y2 < grid_y_e
            d = getDistance([x2, y2], right_inter(1, :));
        end
    end
end