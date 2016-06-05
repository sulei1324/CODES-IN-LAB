function outImage=smooth(src)
inImage=myR2Gray(src);
filledImage=zeroFill(inImage);
fI=filledImage;
[m,n]=size(filledImage);
outImage=zeros(m-2,n-2);
for i=2:m-1
    for j=2:n-1
        toAv=fI(i-1:i+1,j-1:j+1);
        aver=aver9P(toAv);
%         sum9P=fI(i-1,j-1)+fI(i-1,j)+fI(i-1,j+1)+ ...
%             fI(i,j-1)+fI(i,j)+fI(i,j+1)+fI(i+1,j-1)+fI(i+1,j)+fI(i+1,j+1);
%         aver9P=sum9P/9;
        outImage(i-1,j-1)=aver;
    end
end
outImage=uint8(outImage);       %!!!!!! can not ignore this statment
imshow(outImage);
% [g,h]=size(outImage);
% disp(g);
% disp(h);
end