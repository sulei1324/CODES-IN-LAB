function [id,b_id] = findnode(v)
global node_array l;
b_id = l.head_id;
p_id = l.head_id;
flag = 0;
while p_id ~= -1
    if node_array{p_id}.data == v
        flag = 1;
        break;
    end
    b_id = p_id;
    p_id = node_array{p_id}.next_id;
end
    
if flag == 0
    id = -1;
    b_id = -1;
else
    id = p_id;
end


end