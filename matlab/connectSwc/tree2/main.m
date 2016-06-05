clc;
clear all;

global swc_tree N id_stat deepArray widthArray max_degree widthSearchArray;
swc_tree = {};
swc_tree_degree = {};
widthArray = [];
widthSearchArray = [];
N = 100000;
id_stat = zeros(N, 1);
swc = load('G:\sulei\workplace\Swc\res\1.swc');
lines = swc2lines(swc);
max_degree = 0;
leaf_num = 0;
root_id = 1;
deepArray = [];

for i = 1 : size(lines, 1)
    node1 = newNode(lines{i, 1});
    if max_degree < node1.degree
        max_degree = node1.degree;
    end
end

for i = 1 : size(swc_tree, 1)
    node1 = swc_tree{i, 1};
    if size(node1.child_nodes_id, 1) == 0
        leaf_num = leaf_num + 1;
    end
end

for i = 1 : size(swc_tree, 1)
    node1 = swc_tree{i, 1};
    if node1.degree > size(swc_tree_degree, 1)
        swc_tree_degree{node1.degree, 1} = {};
    end
    swc_tree_degree{node1.degree, 1}{size(swc_tree_degree{node1.degree, 1}, 1) + 1, 1} = node1;
end


for i = 1 : size(swc_tree_degree{1, 1}, 1)
    deepTrace(swc_tree_degree{1, 1}{i, 1}.id);
end

for i = 1 : size(swc_tree_degree{1, 1}, 1)
    widthSearchArray = [widthSearchArray, swc_tree_degree{1, 1}{i, 1}.id];
end

search_degree = 1;
while search_degree <= max_degree
    index1 = 1;
    for i = 1 : size(widthSearchArray(search_degree, :), 2)
        if widthSearchArray(search_degree, i) == 0
            continue;
        else
            
            id1 = widthSearchArray(search_degree, i);
            widthArray = [widthArray, id1];
            child_ids = swc_tree{id1, 1}.child_nodes_id;
            if size(child_ids, 1) ~= 0
                for j = 1 : size(child_ids, 2)                
                    widthSearchArray(search_degree + 1, index1) = child_ids(1, j);
                    index1 = index1 + 1;
                end
            end
        end
    end
    search_degree = search_degree + 1;
end
    




% 
% 
% length_degree = [];
% 
% for i = 1 : size(swc_tree_degree, 1)
%     nodes = swc_tree_degree{i, 1};
%     for j = 1 : size(nodes, 1)
%         node1 = nodes{j, 1};
%         length_degree(i, j) = node1.line.length;
%     end
% end



    

