function out_image = enlargeImage(smallImage, s, shrinkFactor)
height= s(1);
width = s(2);
[smallHeight, smallWidth] = size(smallImage);
out_image = zeros(height, width);
xSmallIndices = zeros(1, width);
xWeights = zeros(1, width);
[xSmallIndices, xWeights] = makeInterpolationArrays(xSmallIndices, xWeights, width, smallWidth, shrinkFactor);
% disp(xSmallIndices);
% disp(xWeights);
ySmallIndices = zeros(1, height);
yWeights = zeros(1, height);
[ySmallIndices, yWeights] = makeInterpolationArrays(ySmallIndices, yWeights, height, smallHeight, shrinkFactor);
line0 = zeros(1, width);
line1 = zeros(1, width);
for x = 1:width
    line1(x) = smallImage(1, xSmallIndices(x)) * xWeights(x) + smallImage(1, xSmallIndices(x)+1) * (1 - xWeights(x));
end
ySmallLine0 = 0;
for y = 1:height
    if ySmallLine0 < ySmallIndices(y)
        disp(y);
        swap = line0;
        line0 = line1;
        line1 = swap;
        ySmallLine0 = ySmallLine0 + 1;
        sYPointer = ySmallIndices(y) + 1;
        for x = 1:width
            line1(x) = smallImage(sYPointer, xSmallIndices(x)) * xWeights(x) + smallImage(sYPointer, xSmallIndices(x) + 1) * (1 - xWeights(x));
        end
    end
    weight = yWeights(y);
    for x = 1:width
        out_image(y, x) = line0(x) * weight + line1(x) * (1 - weight);
    end
end
end