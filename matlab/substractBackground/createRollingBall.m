function [ball, shrinkFactor] = createRollingBall(r)


if r <= 10
    shrinkFactor = 1;
    arcTrimPer = 24;
else if r <= 30
        shrinkFactor = 2;
        arcTrimPer = 24;
    else if r <= 100
            shrinkFactor = 4;
            arcTrimPer = 32;
        else
            shrinkFactor = 8;
            arcTrimPer = 40;
        end
    end
end

smallballradius = r / shrinkFactor;
if smallballradius < 1
    smallballradius = 1;
end
disp(smallballradius);
rsquare = smallballradius * smallballradius;
disp(rsquare);
xtrim = floor(arcTrimPer * smallballradius / 100);
disp(xtrim);
halfWidth = floor((smallballradius - xtrim));
width = halfWidth * 2 + 1;
data = zeros(width, width);
for i = [1:width]
    for j = [1:width]
        xval = j - (halfWidth + 1);
        yval = i - (halfWidth + 1);
        temp = rsquare - xval * xval - yval * yval;
        temp = double(temp);
        
        if temp > 0
            data(i, j) = sqrt(temp);
        else
            data(i, j) = 0;
        end
    end
end


ball = data;



end