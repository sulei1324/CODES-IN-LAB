function [swc] = trimSwc(swc)

l = size(swc, 1);

for i = l : -1 : 1
    if(swc(i, 7) == -1)
        swc(i, :) = [];
    else
        break;
    end
end
    




end