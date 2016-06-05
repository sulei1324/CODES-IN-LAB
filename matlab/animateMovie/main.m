clc;
clear all;
%1080p
tic;
model='720p';
I=imread('raw.tif');
swc=load('SpatialGraph1.swc');


if(strcmp(model,'1080p'))
    width=1920;
    height=1080; 
elseif(strcmp(model,'720p'))
    width=1280;
    height=720;
end





[m,n]=size(I);

r_swc=[];
r_swc(:,1:2)=swc(:,3:4);
thresh=50;
new_line=insertLine(r_swc,thresh);
new_line=round(new_line);


l=size(new_line);
for i=1:l
    tmp=[];
    x=new_line(i,1);
    y=new_line(i,2);
    x_s=x-width/2+1;
    x_e=x-width/2+1+width;
    y_s=y-height/2+1;
    y_e=y-height/2+1+height;    
    [x_s,y_s]=checkXYZ(x_s,y_s,n,m);
    [x_e,y_e]=checkXYZ(x_e,y_e,n,m);
    tmp=I(y_s:y_e,x_s:x_e);
    tmp=uint8(tmp);
    imwrite(tmp,['./test/2/' num2str(i,'%05d') '.tif']);
end
toc;

