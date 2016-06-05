function deepTrace(id1)
global swc_tree deepArray;
deepArray = [deepArray, id1];
if size(swc_tree{id1, 1}.child_nodes_id, 1) == 0
    return
else
    for i = 1 : size(swc_tree{id1, 1}.child_nodes_id, 2)
        deepTrace(swc_tree{id1, 1}.child_nodes_id(i));
    end
end
end
