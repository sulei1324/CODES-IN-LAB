clc;

clear all;


data=xlsread('E:\专业课\stat14\练习2修改20141106\练习2数据修改20141106.xls',4,'A2:C73');

[m,n]=size(data);

adType=4;
areaNum=18;
twoX=0;
salesAd=[];
salesArea=[];
salesAdd={};
for i=1:adType
    sale=find(data(:,1)==i);
    s=size(sale,1);
    w=0;
    for j=1:s
        x=find(data(sale,2)==j);

        y=data(sale(x),3);
        salesAd(j,i)=y;
        w=w+y;
        y=num2str(y,'%04d');
        
        salesAdd{j,i}=y;
    end
    
    if(j==s)
        w=w/s;
        oneX(i)=w;
        twoX=twoX+w;
    end
end

salesAreaa={};
for i=1:areaNum
    sale=find(data(:,2)==i);
    s=size(sale,1);
    
    for j=1:s
        x=find(data(sale,1)==j);

        y=data(sale(x),3);
        salesArea(j,i)=y;
        y=num2str(y,'%03d');
        
        salesAreaa{j,i}=y;
    end
end

s=['     广告形式：'];

for i=1:adType
    s=[s '    ' num2str(i)];
end

disp(s);


for i=1:areaNum
    s=['area' num2str(i,'%02d') '的销售额:'];
    for j=1:adType
        s=[s ' ' salesAdd{i,j}];
    end
    disp(s);
end


s=['       地区：'];

for i=1:areaNum
    s=[s '  ' num2str(i,'%02d')];
end

disp(s);


for i=1:adType
    s=['第' num2str(i,'%d') '种广告方式:'];
    for j=1:areaNum
        s=[s ' ' salesAreaa{i,j}];
    end
    disp(s);
end

sse=0;
for i=adType
    for j=1:areaNum
        sse=sse+(str2num(salesAdd{j,i})-oneX(i))^2;
    end
end

ssa=0;
for i=adType
    ssa=ssa+areaNum*(oneX(i)-twoX)^2;
end
        
ssaF=adType-1;
sseF=adType*areaNum--adType;

msa=ssa/ssaF;
mse=sse/sseF;

F=msa/mse;


