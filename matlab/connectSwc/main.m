clc;
clear all;
% part1=load('G:\sulei\allLong\55_part1.swc');
% part2=load('G:\sulei\allLong\55_part2.swc');
test=load('W:\lsu\TDI072\1\den\dendrite_used.swc');

l=size(test,1);

treeIni=find(test(:,7)==-1);
a=size(treeIni,1);
treeCell={};
trueTreeNum=1;

for i=1:a
    if(i==a)
        tmp=test(treeIni(i):end,:);
    else
        tmp=test(treeIni(i):treeIni(i+1)-1,:);
    end
        
    
    if(size(tmp,1)==1)
        continue;
    else   
        treeCell{trueTreeNum,1}=tmp;
        trueTreeNum=trueTreeNum+1;
    end
end

treeNum=size(treeCell,1);
treeStruct={};

for i=1:treeNum
    treeStruct{i,1}=createTree(treeCell{i,1});
end





