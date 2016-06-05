function [ball]=sphericalAreaInPlat(R)
% clc;
% clear all;
% R=5;

index=1;
ball=[];
for i=-R:R
    for j=-R:R
%         for k=-R:R
            if(i^2+j^2<=R^2)
                ball(index,1:2)=[i,j];
                index=index+1;
            end
        end
    end
end

end