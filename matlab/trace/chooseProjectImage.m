function [choosedNum]=chooseProjectImage(zStart,zEnd,pRange)

m=size(pRange,1);
index=1;
choosedNum=[];
for i=1:m
    if(zStart<pRange(i,2)&&zEnd>pRange(i,1))
        choosedNum(index,1)=i;
        index=index+1;
    end
end

end

