function pctTest
tic;
f=zeros(500);
f(1)=1;
f(2)=2;
parfor n=3:5000
    f(n)=n
end
toc;