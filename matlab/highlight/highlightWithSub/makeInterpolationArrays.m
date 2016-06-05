function [smallIndices, weights] = makeInterpolationArrays(smallIndices, weights, length, smallLength, shrinkFactor)
for i = 0 : length - 1
    smallIndex = floor((i - floor(shrinkFactor/2)) / shrinkFactor) + 1;
    if smallIndex == 0
        smallIndex = 1;
    end
    if smallIndex >= smallLength
        smallIndex = smallLength - 1;
    end
    smallIndices(i + 1) = smallIndex;
    distance = (i + 0.5)/shrinkFactor - (smallIndex - 1 + 0.5);
    weights(i + 1) = 1.0 - distance;
end
    





end