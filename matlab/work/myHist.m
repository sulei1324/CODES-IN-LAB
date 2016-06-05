function myHist(string)
imageIn=myR2Gray(string);
[m,n]=size(imageIn);
sumHist=zeros(1,256);
for i=1:m*n
    pixel=imageIn(i)+1;     %原像素范围0`255
    sumHist(pixel)=sumHist(pixel)+1;
end
x=0:255;

plot(x,sumHist);

axis([0,255,0,5]);            %注意设定坐标轴显示范围时axis语句和plot语句的顺序,axis语句在后,plot语句在前.
% figure,plot(sumHist);