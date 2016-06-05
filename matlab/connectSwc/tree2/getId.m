function id1 = getId()
global N id_stat;
for i = 1 : N
    if id_stat(i, 1) == 0
        id1 = i;
        break;
    end
end
id_stat(i, 1) = 1;
end