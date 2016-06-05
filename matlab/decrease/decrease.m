clc;
clear all;

im=imread('./MBA-GF14193_00100_color.jpg');
[height,width,dim]=size(im);
deW=600;
deH=400;
minW=1200;
minH=800;

tmpW=width:-deW:minW;
tmpH=height:-deH:minH;
for i=1:size(tmpH,2)
    disp(i);
    if(i<=23)
        continue;
    else
      tmpIm=im(deH/2*(i-1)+1:deH/2*(i-1)+tmpH(i),deW/2*(i-1)+1:deW/2*(i-1)+tmpW(i),:);
      imwrite(tmpIm,['./im/' num2str(tmpW(i)) '-' num2str(tmpH(i)) '.jpg'])
    end
end