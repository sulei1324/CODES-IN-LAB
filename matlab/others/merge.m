clc;
clear all;


a = imread('W:\lsu\TDI072\figure\3\all_cell\bouton\figure\snapshot_brain_g.tif');
b = imread('W:\lsu\TDI072\figure\3\all_cell\bouton\figure\snapshot_cell.tif');


[l, m, n] = size(a);


for i = 1 : l
    for j = 1 : m
        if b(i, j, 1) == 0 && b(i, j, 2) == 0 && b(i, j, 3) == 0
            continue;
            
        else
            a(i, j, 1) = b(i, j, 1);
            a(i, j, 2) = b(i, j, 2);
            a(i, j, 3) = b(i, j, 3);
        end
    end
end

imwrite(a, 'W:\lsu\TDI072\figure\3\all_cell\bouton\figure\snapshot_all.tif');

     
        