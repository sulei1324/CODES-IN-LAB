function [x,y]=checkXY(x,y,width,height)

if(x>width)
    x=width;
end

if(x<1)
    x=1;
end

if(y>height)
    y=height;
end

if(y<1)
    y=1;
end

end

% if(z>zRange)
%     z=zRange;
% end
% 
% if(z<1)
%     z=1;
% end
