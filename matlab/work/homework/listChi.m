clc;

clear all;

data=xlsread('E:\רҵ��\stat14\��ϰ2�޸�20141106\��ϰ2�����޸�20141106.xls',2,'B2:E4');

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
