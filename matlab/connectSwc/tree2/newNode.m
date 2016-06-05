function node = newNode(line1)
global swc_tree;
node = struct();
node.id = getId();
node.line = line1;
node.father_id = findFatherId(node.line);
if strcmp(node.father_id, 'root')
    node.degree = 1;
else
    node.degree = swc_tree{node.father_id, 1}.degree + 1;
    swc_tree{node.father_id, 1}.child_nodes_id = [swc_tree{node.father_id, 1}.child_nodes_id, node.id];
end
node.child_nodes_id = [];
swc_tree{node.id, 1} = node;
end