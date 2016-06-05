% function mallHist(exl,n_start,n_end,d)
clc;
clear all;
num=xlsread('E:\רҵ��\��ϰ1\��ϰ1\��ϰ1����.xls',4,'B2:B22');
analysisData(num,'����2');
uni_num=unique(num);
m=size(uni_num,1);
n_start=min(num(:));
n_end=max(num(:));
groupDistance=0.1;
lastBit=0.01;
group_ini=[n_start:groupDistance:n_end];
groupNum=size(group_ini,2);
group=zeros(2*groupNum,1);
for i=1:groupNum
    s=group_ini(i);
    group(2*i-1,1)=s;
    if(i==groupNum)
        e=n_end;
    else
        e=group_ini(i+1)-lastBit;
    end
    group(2*i,1)=e;
    

end


for i=1:groupNum
    n=0;
    for j=group(2*i-1):lastBit:group(2*i)
        test_b=0;
        test_a=0;
        test_a=find((num<=j+100*eps)&(num>=j-100*eps));
        test_b=size(test_a,1);
        n=n+test_b;
    end
    disp(['group ' num2str(i,'%d') ' (' num2str(group(2*i-1),'%04d') '-' num2str(group(2*i),'%04d') ') has ' num2str(n,'%04d') ' elements']);
end

disp(['Range      Frequency']);
y=[];
for i=1:groupNum
    n=0;
    
    for j=group(2*i-1):lastBit:group(2*i)
        test_b=0;
        test_a=0;
        test_a=find((num<=j+100*eps)&(num>=j-100*eps));
        test_b=size(test_a,1);
        n=n+test_b;
    end
    y=[y,n];
    disp([num2str(group(2*i-1),'%04d') '-' num2str(group(2*i),'%04d') '      '  num2str(n,'%04d')]);
end

x=n_start+2*lastBit:groupDistance:n_end;
x=[];
for i=1:groupNum
    groupS=group(2*i-1);
    groupE=group(2*i);
    groupM=(groupS+groupE)/2;
    x=[x,groupM];
end

% bar(x,y);

% hist(num,x);

histHeight=max(y)+5;
histWidth=3+8*groupNum;
lineLocation=[6:8:histWidth];
gLocation=[4:8:histWidth];
rLocation=[5:8:histWidth];
oLocation=[6:8:histWidth];
uLocation=[7:8:histWidth];
pLocation=[8:8:histWidth];
indexLocation=[9:8:histWidth];
histCell={};
flag=0;
for i=1:histHeight
    if(i==1)
        groupIndex=1;
        for j=1:histWidth
            
            
            if(j==1)
                histCell{i,j}=num2str(i-1,'%04d');
                continue;
            end
            if(size(find(gLocation==j))~=0)
                histCell{i,j}='g';
                continue;
            end
            if(size(find(rLocation==j))~=0)
                histCell{i,j}='r';
                continue;
            end           
            if(size(find(oLocation==j))~=0)
                histCell{i,j}='o';
                continue;
            end        
            if(size(find(uLocation==j))~=0)
                histCell{i,j}='u';
                continue;
            end     
            if(size(find(pLocation==j))~=0)
                histCell{i,j}='p';
                continue;
            end                
             
            if(size(find(indexLocation==j))~=0)
                histCell{i,j}=num2str(groupIndex);
                groupIndex=1+groupIndex;
                continue;
            end
            histCell{i,j}=' ';
            
        end
        continue;
    end
    for j=1:histWidth
        if(j==1)
            histCell{i,j}=num2str(i-1,'%04d');
            continue;
        end
        histCell{i,j}=' ';
    end
end

lineN=size(lineLocation,2);
for i=1:lineN
    lineL=y(i);
    columnL=lineLocation(i);
    for j=1+1:lineL+1
        histCell{j,columnL}='|';
    end
end
    
for i=1:histHeight
    dispColumnNum=histHeight+1-i;
    dispContent=[];
    for j=1:histWidth
        dispContent=[dispContent,histCell{dispColumnNum,j}];
        
    end
    disp(dispContent);
end
    




% end