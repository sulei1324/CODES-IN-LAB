function [n] = node(d)
global node_array;
if canallocation()    
    n.id = allocationID();
else
    disp('can not allocation new node.');
    n = 0;
    return;
end
n.data = d;
n.next_id = -1;
node_array{n.id} = n;
end