function t = getTerminals(swc)
l = size(swc, 1);
t = [];
if l < 2
    t = swc;
    return;
end
for i = 2 : l
    if swc(i, 7) ~= swc(i, 1) - 1
       t = [t; swc(i - 1, :)];
    end
end
t = [t; swc(i, :)];
end