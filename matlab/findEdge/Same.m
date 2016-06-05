function Same()


a=imread('H:\sulei\ÂÖÀªÖÆ×÷\test_05501_montage_edge.tif');
b=im2bw(a);
[m,n]=size(a);


for i=1:m
    for j=1:n
        if(a(i,j)==255)
            a(i,j)=1;
        end
    end
end

dif_num=0;

for i=1:m
    for j=1:n
        if(a(i,j)~=b(i,j))
            dif_num=dif_num+1;
        end
    end
end

disp(dif_num);

end