function m = getMinMax(im)

min = 256;
max = -1;
[y, x] = size(im);
for i = 1:y
    for j = 1:x
        if im(i, j) > max
            max = im(i, j);
        else if im(i, j) < min
                min = im(i, j);
            end
        end
    end
end

m = [min, max];

end