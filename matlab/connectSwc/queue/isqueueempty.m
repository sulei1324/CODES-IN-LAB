function [flag] = isqueueempty()
global a;
if a.head  == a.tail
    flag = true;
else
    flag = false;
end

end