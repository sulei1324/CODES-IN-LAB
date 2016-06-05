clc;
clear all;
tic;
global l M node_array id_array;

M = 5000;
id_array = zeros(1,M);
node_array = cell(1,M);
l = list();
for i = 1:5:100
    if ~canallocation()
        is = num2str(i-1,'%04d');
        disp(['reach ',is]);
        disp('can not allocate new!');
        break;
    end
    n = node(i);
    append(n);
    
end
insertnode4queue(4);


toc;

