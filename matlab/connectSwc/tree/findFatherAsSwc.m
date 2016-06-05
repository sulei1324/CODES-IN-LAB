function id = findFatherAsSwc(d, p_id)
global node_array;
disp(d);
disp(p_id);
if p_id == -1
    id = -1;
    return;
end
line_start = d(1,7);
while p_id ~= -1
    p_range = [node_array{1,p_id}.data(1,1),node_array{1,p_id}.data(end,1)];
    if p_range(1) < line_start && line_start < p_range(2)
        id = p_id;
        return
    else
        p_id = node_array{1,p_id}.father_id;
        id = p_id;
    end
end



end