% the second edition ͼ��ת��������������.

function outImage=rollover(inImage)
[m,n]=size(inImage);
tempImage=inImage;
% M=max(m,n);
% tempImage(M,M)=0;
% for i=1:M
%     for j=1:M
%         if(i<=j)
%         [tempImage(i,j),tempImage(j,i)]=mySwap(tempImage(i,j),tempImage(j,i));
%     end
%     end
% end
% outImage(1:n,1:m)=tempImage(1:n,1:m);
for i=1:m
    for j=1:n
        outImage(j,i)=tempImage(i,j);
    end
end
end
        ]