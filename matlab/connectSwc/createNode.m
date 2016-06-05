function [node] = createNode( data)
node = struct();
node.data = data;
node.father = struct();
node.firstson = struct();
node.son_num = 0;
end

