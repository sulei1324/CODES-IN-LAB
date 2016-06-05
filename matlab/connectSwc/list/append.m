function append(n)
global l node_array;
if l.length == 0
    l.head_id = n.id;
else
    p_id = l.head_id;
    while node_array{p_id}.next_id ~= -1
        p_id = node_array{p_id}.next_id;
    end
    node_array{p_id}.next_id = n.id;
end

l.length = l.length + 1;

end