function [flag] = isqueuefull()
global a M;
if a.tail > M
    flag = true;
else
    flag = false;
end
end