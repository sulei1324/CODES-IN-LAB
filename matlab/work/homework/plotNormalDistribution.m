function plotNormalDistribution(u,sigma)

x=u-15:u+15;
% y=gaussmf(x,[sigma u]);
y=normpdf(x,u,sigma);
axis([u-100 u+100 0 100]);
plot(x,y);

end