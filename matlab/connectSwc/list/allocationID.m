function [id] = allocationID()
global id_array;

id = find(id_array == 0, 1, 'first');
id_array(id) = 1;
end