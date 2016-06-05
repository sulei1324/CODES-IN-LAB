function [tree,node] = add2tree(node, father, tree)
if tree.node_num == 0
    tree.root = node;
end
node.father = father;    
tree.node_num = tree.node_num + 1;
    





end