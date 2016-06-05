clc;
clear;

for i=40:57
for j=31:60
    if(j==31)
        c=[]
    end
    J=sprintf('W:\\lsu\\guorui\\src\\00006\\test_00006_%d_%d.jpg',i,j);    
    d=imread(J);
    c=[c;d];  
end
if(i==40)    
    e=c; 
    f=e;
else
    f=[f e];
end
end



imwrite(f,'C:\Users\苏雷\Desktop\报告总结\test_000061.jpg')





    