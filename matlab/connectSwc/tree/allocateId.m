function id = allocateId()
global id_array;
id = find(id_array == 0, 1, 'first');
id_array(1,id) = 1;



end