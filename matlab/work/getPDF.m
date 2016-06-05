function pdf=getPDF(h,i)
[m,n]=size(i);
pdf=zeros(256,1);
for k=1:256
    pdf(k)=h(k)/(m*n);
end
