function insertSwcNode(n,father_id)
global node_array t;



if father_id == -1
    t.root_id = n.id;
    t.depth = t.depth + 1;
    
else
    t.depth = t.depth + 1;
    p_id = node_array{1,father_id}.firstchild_id;
    b_id = p_id;
    flag = 0;
    while p_id ~= -1
        if node_array{1,p_id}.data(1,1) > n.data(1,1)
            flag = 1;
            break;
        end
        b_id = p_id;
        p_id = node_array{1,p_id}.rightsibling_id;
    end

    if flag == 1
        node_array{1,b_id}.rightsibling_id = n.id;
        node_array{1,n.id}.rightsibling_id = p_id;
    else if p_id == -1 && b_id == -1
            node_array{1,father_id}.firstchild_id = n.id;
        else
            node_array{1,father_id}.firstchild_id = n.id;
            node_array{1,n.id}.rightsibling_id = b_id;
        end
    end
    node_array{1,n.id}.father_id = father_id;

end
end




