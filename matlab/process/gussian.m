function [H]=gussian(k,sigma)



H=zeros(2*k+1,2*k+1);

a=2*pi*(sigma^2);
b=2*(sigma^2);

for i=1:2*k+1
    c=(i-k-1)^2;
    for j=2:2*k+1
        d=(j-k-1)^2;
        f=-(c+d)/b;
        H(i,j)=a*exp(f);
    end
end
Hsum=sum(sum(H));
H=H/Hsum;


end
