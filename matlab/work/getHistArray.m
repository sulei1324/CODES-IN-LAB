function histArray=getHistArray(i)
[m,n]=size(i);
% for uint8
histArray=zeros(256,1);
for j=1:m
    for k=1:n
        histArray(i(j,k)+1)=histArray(i(j,k)+1)+1;
    end
end
