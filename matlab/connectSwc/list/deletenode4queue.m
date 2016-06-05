function deletenode4queue(value)
global node_array l;
[id, b_id] = findnode(value);
if id == -1
    disp('no');
    return
elseif id == b_id
        l.head = node_array{id}.next_id;
else
    node_array{b_id}.next_id = node_array{id}.next_id;

end
deletenode(id);
l.length = l.length - 1;

end