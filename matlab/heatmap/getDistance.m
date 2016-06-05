function d = getDistance(p1, p2)

x1 = p1(1);
x2 = p2(1);
y1 = p1(2);
y2 = p2(2);
d = (x2 - x1) ^ 2 + (y2 - y1) ^ 2;
d = sqrt(d);
end