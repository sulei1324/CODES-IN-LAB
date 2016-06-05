function [pRange]=projectRange(file)

f=dir(file);
fNum=size(f,1);
pRange=zeros(fNum-2,2);

for i=3:fNum
    fName=f(i).name;
    firstNumStart=1;
    n=find(fName=='-');
    firstNumEnd=n(1,1)-1;
    firstNum=fName(firstNumStart:firstNumEnd);
    secondNumStart=n(1,1)+1;
    m=find(fName=='_');
    secondNumEnd=m(1,1)-1;
    secondNum=fName(secondNumStart:secondNumEnd);
    pRange(i-2,1)=str2num(firstNum);
    pRange(i-2,2)=str2num(secondNum);
end

% pRange=sortrows(pRange);

end
    