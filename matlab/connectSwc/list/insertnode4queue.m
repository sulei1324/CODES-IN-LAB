function insertnode4queue(value)
global node_array l;
if canallocation()
    n = node(value);
end
b_id = l.head_id;
p_id = l.head_id;
while p_id ~= -1
    if node_array{p_id}.data > value
        break;
    end
    b_id = p_id;
    p_id = node_array{p_id}.next_id;
end
if p_id == l.head_id
    node_array(n.id).next_id = p_id;
    l.head_id = n.id;
elseif p_id == -1
    append(n);
else
    node_array{b_id}.next_id = n.id;
    node_array{n.id}.next_id = p_id;
end
l.length = l.length + 1;
   


end