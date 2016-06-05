function [swc] = trimSwc(swc)

l = size(swc, 1);

for i = l : -1 : 1
    if(swc(l, 7) == -1)
        swc(l, :) = [];
    else
        break;
    end
end
    




end