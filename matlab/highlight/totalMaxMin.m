function [max3,min3] = totalMaxMin(max1,max2,min1,min2)
%TOTALMAXMIN Summary of this function goes here
%   Detailed explanation goes here
max3=zeros(1,3);
min3=zeros(1,3);

if(max1(1,1)>max2(1,1))
    max3(1,1)=max1(1,1);
else
    max3(1,1)=max2(1,1);
end
if(max1(1,2)>max2(1,2))
    max3(1,2)=max1(1,2);
else
    max3(1,2)=max2(1,2);
end
if(max1(1,3)>max2(1,3))
    max3(1,3)=max1(1,3);
else
    max3(1,3)=max2(1,3);
end
if(min1(1,1)<min2(1,1))
    min3(1,1)=min1(1,1);
else
    min3(1,1)=min2(1,1);
end
if(min1(1,2)<min2(1,2))
    min3(1,2)=min1(1,2);
else
    min3(1,2)=min2(1,2);
end
if(min1(1,3)<min2(1,3))
    min3(1,3)=min1(1,3);
else
    min3(1,3)=min2(1,3);
end







end

