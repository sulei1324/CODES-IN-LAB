function in_image = rollBall(ball, in_image)

[height, width] = size(in_image);

ballWidth = size(ball, 1);

radius = floor(ballWidth / 2);

cache = zeros(ballWidth, width);
y = -radius + 1;
while y <= height + radius
    nextLineToWriteInCache = mod(y + radius, ballWidth);
    if nextLineToWriteInCache == 0
        nextLineToWriteInCache = 3;
    end
    nextLineToRead = y + radius;
    if nextLineToRead <= height
        cache(nextLineToWriteInCache, :) = in_image(nextLineToRead, :);
        x = 1;
        p = nextLineToRead;
        while x <= width
            in_image(p, x) = -10000;
            x = x + 1;
        end
    end
    y0 = y - radius;
    if y0 < 1
        y0 = 1;
    end
    yBall0 = y0 - y + radius + 1;
    yEnd = y + radius;
    if yEnd > height
        yEnd = height;
    end
    x = -radius + 1;
    while x <= width + radius
        z = 256;
        x0 = x -radius;
        if x0 < 1
            x0 = 1;
        end
        xBall0 = x0 - x + radius + 1;
        xEnd = x + radius;
        if xEnd > width
            xEnd = width;
        end
        yp = y0; 
        yBall = yBall0;
        while yp <= yEnd
            cachePointer = mod(yp, ballWidth);
            if cachePointer == 0
                cachePointer = 3;
            end
            xp = x0;
            bp = xBall0;
            while xp <= xEnd
                zReduced = cache(cachePointer, xp) - ball(yBall, bp);
                if z > zReduced
                    z = zReduced;
                end
                xp = xp + 1;
                bp = bp + 1;                
            end
            yp = yp + 1;
            yBall = yBall + 1;
        end
        yp = y0;
        yBall = yBall0;
        while yp <= yEnd
            xp = x0;
            bp = xBall0;
            while xp <= xEnd
                zMin = z + ball(yBall, bp);
                if in_image(yp, xp) < zMin  
                    in_image(yp, xp) = zMin;
                end
                xp = xp + 1;
                bp = bp + 1;                
            end
            yp = yp + 1;
            yBall = yBall + 1;
        end
        x = x + 1;
    end
    y = y + 1;
end
                
    


end