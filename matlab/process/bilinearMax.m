function [outImage]=bilinearMax(inImage,R)

L=2*R+1;
v=floor(L/2);

[m,n]=size(inImage);

rowLast=m-mod(m-1,v);
colLast=n-mod(n-1,v);
rowAppend=v-mod(m-1,v);
colAppend=v-mod(n-1,v);

tmpImage=zeros(m+rowAppend,n+colAppend);
tmpImage(1:m,1:n)=inImage;

for i=1:m
    tmpImage(i,n+colAppend)=inImage(i,colLast);
end

for i=1:n+colAppend
    tmpImage(m+rowAppend,i)=tmpImage(rowLast,i);
end

[a,b]=size(tmpImage);
tmp=tmpImage;


for i=1:a
    for j=1:b
        if((j==b)||(i==a)||(mod(i-1,v)==0)&&(mod(j-1,v)==0))
            continue;
        end
        dUp=mod(i-1,v);
        dDown=v-mod(i-1,v);
        dLeft=mod(j-1,v);
        dRight=v-mod(j-1,v);
        nUp=i-dUp;
        nDown=i+dDown;
        nLeft=j-dLeft;
        nRight=j+dRight;
%         disp(nUp);
%         disp(nDown);
%         disp(nLeft);
%         disp(nRight);
        up=tmp(nUp,nLeft)*(v-dLeft)/v+tmp(nUp,nRight)*(v-dRight)/v;
        down=tmp(nDown,nLeft)*(v-dLeft)/v+tmp(nDown,nRight)*(v-dRight)/v;
        tmpImage(i,j)=up*(v-dUp)/v+down*(v-dDown)/v;
    end
end

outImage=tmpImage(1:m,1:n);

end


