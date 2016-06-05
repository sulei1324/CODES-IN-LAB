function id = findnode(v)
global t node_array;
p_id = t.root_id;
flag = 0;
while p_id ~= -1
    if node_array{1,p_id}.data == v
        flag = 1;
        id = p_id;
        break;
    else
        if node_array{1,p_id}.firstchild_id ~= -1
            p_id = node_array{1,p_id}.firstchild_id;
        else if node_array{1,p_id}.rightsibling_id ~= -1
                p_id = node_array{1,p_id}.rightsibling_id;
            else
                p_id = node_array{1, node_array{1,p_id}.father_id}.rightsibling_id;
            end
        end
    end
end
if flag == 0
    id = -1;
end

end