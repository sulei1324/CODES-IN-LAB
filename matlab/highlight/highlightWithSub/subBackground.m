function [outImage] = subBackground(inImage)

% clc;
% clear all;

raw_image = inImage;
raw_image = double(raw_image);


[height, width] = size(raw_image);
radius = 50;
[ball, shrinkFactor] = createRollingBall(radius);
shrink = shrinkFactor > 1;

doPresmooth = true;
if doPresmooth
    smooted_image = filter3x3(raw_image, 'mean');
end



minmax = getMinMax(smooted_image);

if shrink
    smallImage = shrinkImage(smooted_image, shrinkFactor);
else
    smallImage = smooted_image;
end

smallImage = rollBall(ball, smallImage);

outImage = enlargeImage(smallImage, [height, width], shrinkFactor);
outImage = uint8(outImage);
raw_image = uint8(raw_image);
outImage = raw_image - outImage;
% imwrite(outImage,'raw_bg.tif');


end
    