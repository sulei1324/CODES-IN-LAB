function myHist(string)
imageIn=myR2Gray(string);
[m,n]=size(imageIn);
sumHist=zeros(1,256);
for i=1:m*n
    pixel=imageIn(i)+1;     %ԭ���ط�Χ0`255
    sumHist(pixel)=sumHist(pixel)+1;
end
x=0:255;

plot(x,sumHist);

axis([0,255,0,5]);            %ע���趨��������ʾ��Χʱaxis����plot����˳��,axis����ں�,plot�����ǰ.
% figure,plot(sumHist);