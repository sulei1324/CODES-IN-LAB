i=input('i(n)=');
j=input('j(n)=');
i_l=size(i,2);

j_l=size(j,2);

num=i_l+j_l-1;

y=zeros(num,1);
i(i_l+1:num)=0;
j(j_l+1:num)=0;
for n=1:num
    for k=1:n
        y(n)=y(n)+i(k)*j(n+1-k);   % n+1-k��ԭ������Ϊ�±��1��ʼ,���֮ǰ��n-k(������������)ҲҪ˳�ż���1,����ȷ.
    end
end
disp(y);



    
    

