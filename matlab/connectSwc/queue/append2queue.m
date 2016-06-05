function append2queue(d)
global a;
if isqueuefull()
    disp('reach the end!');
    return;
end
a.data(a.tail) = d;
a.tail = a.tail + 1;
end