function n = node(d)
global node_array;
n = struct();
n.id = allocateId();
n.data = d;
n.father_id = -1;
n.firstchild_id = -1;
n.rightsibling_id = -1;
n.degree = 0;
node_array{1, n.id} = n;

end