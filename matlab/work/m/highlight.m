clc;

clear all;

A=imread('grass.jpg');

B1=rgb2gray(A);

imshow(B1);


[m,n]=size(B1);



x=round(m/2);

y=round(n/2);

% for i=1:m
%     for j=1:n
%         if(i<100|i>300)
% %         if(100<i&i<300)
%             disp(i);
%             B(i,j)=B1(i,j)*0.6;
%             disp('here');
%         else
%             B(i,j)=B1(i,j);
%             disp('there');
%             
%         end
%     end
% end

% B=uint8(B);

a=m;

if(m>n)
    a=n;
end

% for i=1:m
%     for j=1:n
%         if(i==j)
%             B(i,j)=B1(i,j);
%             disp('here');
%         else
%             B(i,j)=B1(i,j)*0.01;
%         end
%     end
% end

B=B1;

for i=1:a
    B(i:end,i)=B1(i:end,i)*0.01;
end


        



imshow(B);
    