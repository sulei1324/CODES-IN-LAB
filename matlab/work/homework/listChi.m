clc;

clear all;

data=xlsread('E:\专业课\stat14\练习2修改20141106\练习2数据修改20141106.xls',2,'B2:E4');

% data=data';

[s,r]=size(data);

n=sum(data(:));

ni=sum(data);

nj=sum(data');

for i=1:r
    for j=1:s
        x=(n*data(j,i)-ni(i)*nj(j))^2/(n*ni(i)*nj(j));
    end
end
