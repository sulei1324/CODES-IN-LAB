function [outImage]=mirrorBundary(inImage,R)

[m,n]=size(inImage);

outImage=zeros(m+2*R,n+2*R);

outImage(R+1:R+m,R+1:R+n)=inImage(:,:);

% up

for i=1:R
    outImage(i,R+1:R+n)=inImage(R+1-i,:);
end

% down
for i=R+m+1:2*R+m
    outImage(i,R+1:R+n)=inImage(R+2*m+1-i,:);
end

% left
for i=1:R
    outImage(:,i)=outImage(:,2*R+1-i);
end

% right
for i=R+n+1:2*R+n
    outImage(:,i)=outImage(:,2*R+2*n+1-i);
end

end