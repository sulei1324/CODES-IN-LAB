function [outImage]=chooseMax(inImage,R)

[m,n]=size(inImage);
outImage=zeros(m-2*R,n-2*R);

% rollingball radius = R, so sliding window's side length = L
L=2*R+1;
% velocity
v=floor(L/2);


temp=zeros(m,n);
tempR=zeros(L,L);
tempM=zeros(1,2*R+1);

% raw_image:1+R:m-R,1+R:n-R

for i=1+R:v:m-R
    for j=1+R:v:n-R
        tempR=inImage(i-R:i+R,j-R:j+R);
        tempM=max(tempR);
        temp(i,j)=max(tempM(:));
        
    end
end

outImage=temp(1+R:m-R,1+R:n-R);

end