function delete2queue()
global a M;
if a.head == a.tail
    disp('empty!');
    return;
end
a.data(a.head) = [0];
a.head = a.head + 1;
if a.head > M
    disp('empty');
end

end