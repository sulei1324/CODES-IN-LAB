clc;
clear all;

global M a;
M = 100;
a = queue(M);

for i = 1:100
    append2queue(i);
end

for i = 1:100
    delete2queue();
end