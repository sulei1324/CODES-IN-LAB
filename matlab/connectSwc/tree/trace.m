function trace()
global t node_array;
p_id = t.root_id;
while p_id ~= -1
    disp(node_array{1,p_id}.data);
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

