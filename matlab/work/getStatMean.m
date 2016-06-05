function statMean=getStatMean(i)
h=getHistArray(i);
[m,n]=size(i);
p=getPDF(h,i);
statMean=0;
for k=1:256
    statMean=statMean+p(k)*k;
end
end

