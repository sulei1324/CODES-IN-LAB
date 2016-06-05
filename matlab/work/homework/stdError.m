function [output] = stdError(input)

m=size(input,1);
if(m==1)
    disp('can not do this operate,caus m=1.');
    output=NaN;
    return;
end
output=0;
for i=1:m
    output=power(input(i,1),2)+output;
end

output=output/(m-1);

end
    


