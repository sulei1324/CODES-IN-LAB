function flag = canallocation()
global id_array;
id = find(id_array == 0,1);
if size(id,1) == 1 && size(id,2) == 0
    flag = 0;
else
    flag = 1;
end
end