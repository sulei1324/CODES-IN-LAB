function [in_image, shiftBy] = filter3(in_image, length, pixel0, inc, type)

shiftBy = 0;
i = 0;
p = pixel0;
v3 = in_image(pixel0);
v2 = v3;

while i < length
    v1 = v2;
    v2 = v3;

    if i < length -1
        v3 = in_image(p+inc);
    end

    if strcmp(type, 'MAXIMUM')
        if v1 > v3
            max = v1;
        else
            max = v3;
        end
        if v2 > max
            max = v2;
        end
        shiftBy = shiftBy + max - v2;
        in_image(p) = max;
    else

        in_image(p) = ((v1 + v2 + v3)*1/3);
    end
    p = p + inc;
    i = i + 1;
end


end