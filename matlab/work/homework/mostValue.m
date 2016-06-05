function [output] = mostValue(input)

m=size(input,1);
uniInput=unique(input,'rows');
uM=size(uniInput,1);
num=zeros(uM,1);
for i=1:uM
    value=uniInput(i);
    a=find(input==value);
    uniInput(i,2)=size(a,1);
end

maxNum=max(uniInput(:,2));
outputNum=find(uniInput(:,2)==maxNum);

for i=1:size(outputNum,1)
    output(i)=uniInput(outputNum(i),1);
end

end
    



