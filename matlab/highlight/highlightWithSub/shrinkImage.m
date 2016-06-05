function smallImage = shrinkImage(in_image, shrinkFactor)
[height, width] = size(in_image);
sWidth = floor((width + shrinkFactor - 1) / shrinkFactor);
sHeight = floor((height + shrinkFactor - 1) / shrinkFactor);

smallImage = zeros(sHeight, sWidth);
for ySmall = 1:sHeight
    for xSmall = 1:sWidth
        min = 256;
        j = 0;
        y = shrinkFactor * ySmall;
        while j < shrinkFactor && y <= height
            k = 0;
            x = shrinkFactor * xSmall;
            while k < shrinkFactor && x <= width
                thispixel = in_image(y, x);
                if thispixel < min
                    min = thispixel;
                end
                k = k + 1;
                x = x + 1;
            end
            j = j + 1;
            y = y + 1;
        end
        
        smallImage(ySmall, xSmall) = min;
    end
end



            



end