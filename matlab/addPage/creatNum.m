function [fontNum]=creatNum()

numArray={};

arrayRaw={};
arrayRaw{10,1}=[1 2 3 4 5 6 10 11 12 13 14 15];
arrayRaw{1,1}=[6 7 8 9 10];
arrayRaw{2,1}=[1 3 4 5 6 8 10 11 12 13 15];
arrayRaw{3,1}=[1 6 11 12 13 8 3 14 15 5 10];
arrayRaw{4,1}=[1 2 3 8 13 12 11 14 15];
arrayRaw{5,1}=[1 6 11 2 3 8 13 14 15 10 5];
arrayRaw{6,1}=[11 6 1 2 3 8 13 4 14 5 10 15];
arrayRaw{7,1}=[1 6 11 12 13 14 15];
arrayRaw{8,1}=[1 2 3 4 5 6 10 11 12 13 14 15 8];
arrayRaw{9,1}=[1 6 11 2 12 3 8 13 14 15];
fontNum={};
for i=1:10
    fontRaw=zeros(5,3);
    pointI=arrayRaw{i,1};
    l=size(pointI,2);
    for j=1:l
        fontRaw(pointI(j))=1;
    end
    fontNum{i,1}=fontRaw;
end
    