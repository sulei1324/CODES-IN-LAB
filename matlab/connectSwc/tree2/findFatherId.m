function f_id = findFatherId(line1)
global swc_tree;
line1_start_serial = line1.pdata(1, 1);
if line1.pdata(1, 7) == -1
    f_id = 'root';
    return;
end
for i = 1 : size(swc_tree, 1)
    this_node = swc_tree{i, 1};
    this_line_serials = this_node.line.pdata(:, 1);
    if size(find(this_line_serials == line1_start_serial), 2) ~= 0 && size(find(this_line_serials == line1_start_serial), 1)
        f_id = i;
        break;
    end
end
end