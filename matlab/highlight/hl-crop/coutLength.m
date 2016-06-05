clc;
clear all;


swc=load('W:\lsu\TDI072\figure\3\all_cell\swc\3_branch5.swc');
line=readLine(swc);
lineNum=size(line,1);
whole_l = 0;

for i = 1 : lineNum
    disp('start');
    this_line = line(i);
    node_num = size(this_line{1}, 1);
    for j = 1 : node_num
        if j == 1
            l = 0;
            continue;
        end
        this_node = this_line{1}(j, :);
        pre_node = this_line{1}(j - 1, :);
%         disp(pre_node);
%         disp(this_node);
        disp((((this_node(3) - pre_node(3)) * 0.3) ^ 2 + ((this_node(4) - pre_node(4)) * 0.3) ^ 2 + ((this_node(5) - pre_node(5))) ^ 2));
        l = l + sqrt(((this_node(3) - pre_node(3)) * 0.3) ^ 2 + ((this_node(4) - pre_node(4)) * 0.3) ^ 2 + ((this_node(5) - pre_node(5))) ^ 2);
        disp(l);
    end
    whole_l = whole_l + l;
end

whole_l = whole_l / 1000;