% function Leng = CountLength( AA )

clc;
clear all;

AA = load('W:\lsu\TDI072\figure\3\all_cell\swc\3_branch5.swc');

Leng = 0;

for i = 1 : size( AA , 1 )
    if AA( i , 7 ) == AA( i , 1 ) - 1
        L = AA(i,3:5) - AA(i-1,3:5);
        L(1) = L(1) * 0.3;
        L(2) = L(2) * 0.3;
        %L(3) = L(3);
        Leng = Leng + norm( L );
    end
end

Leng = Leng/1000;

