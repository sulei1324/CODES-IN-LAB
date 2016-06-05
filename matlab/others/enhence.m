clc;

clear all;

src='Y:\Public\mostzhangyalun\sulei\matlab\4.jpg';

A=imread(src);
A=rgb2gray(A);
% imhist(A);
% figure,imhist(A);

[m,n]=size(A);

% A=double(A);
I=A;

I=imadjust(I);

I=uint8(I);
imshow(I);

imwrite(I,'../2.tif');

% for i=1:m
%     B(i,1)=max(A(:,i));
% end
% 
% figure,plot(B);
% 
% C=find(B==0);
% 
% l=size(C,1);
% 
% D=B;
% 
% for i=1:l
%     i
%     D(C(i),1)=1;
% end
% 
% 
% mD=max(D(:,1));
% 
% 
% 
% 
% E=mD./D;
% 
% figure,plot(E);
% 
% 
% for i=1:m
%     for j=1:n
% %         if(A(i,j)~=255)
%             I(i,j)=A(i,j)*3;
% %         end
%     end
% end
% 
% I=uint8(I);
% 
% 
% % A=imadjust(A);
% % 
% % figure, imhist(A);
% 
% % imshow(I);
% 
% imwrite(I,'../9.tif');




            