clc;
clear all;

global node_array id_array M t;

M = 10;
node_array = cell(1,M);
id_array = zeros(1,M);
t = tree();
n1 = node(1);
n2 = node(2);
n3 = node(3);
n4 = node(4);
n5 = node(5);
insertnode(n1,-1);
insertnode(n2,n1.id);
insertnode(n3,n1.id);
