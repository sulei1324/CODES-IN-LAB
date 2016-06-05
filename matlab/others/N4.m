function [pUp,pDown,pLeft,pRight]=N4(i,j,m,n)
if(i==1)
    pUp=1;
else
    pUp=i-1;
end
if(i==m)
    pDown=m;
else
    pDown=i+1;
end
if(j==1)
    pLeft=1;
else
    pLeft=j-1;
end
if(j==n)
    pRight=n;
else
    pRight=j+1;
end

end