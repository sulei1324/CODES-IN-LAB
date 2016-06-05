function [x,y]=checkXY(x,y,width,height)

if(x(1,2)>width)
    x(1,2)=width;
end

if(x(1,1)<1)
    x(1,1)=1;
end

if(y(1,2)>height)
    y(1,2)=height;
end

if(y(1,1)<1)
    y(1,1)=1;
end

end
