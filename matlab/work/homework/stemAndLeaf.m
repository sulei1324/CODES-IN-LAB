function  stemAndLeaf(xlsDir,sheetNum,columnRange)
%UNTITLED1 Summary of this function goes here
%  Detailed explanation goes here

myData=xlsread(xlsDir,sheetNum,columnRange);
arrayNum=size(myData,1);
stemArray=myData/10;
stemArray=floor(stemArray);
stemArray=unique(stemArray);
stemNum=size(stemArray,1);


for i=1:stemNum   
    leaf{i,1}=[];
end


for i=1:arrayNum
    x=floor(myData(i)/10);
    for j=1:stemNum
        
        if(x==stemArray(j))
            y=mod(myData(i),10);
            leaf{j,1}=[leaf{j,1};y];
            break;
        end
    end
end


for i=1:stemNum
    stemAndLeafFigure(i).stem=stemArray(i);
    x=leaf{i,1};
    x=sortrows(x);
    stemAndLeafFigure(i).leaf=x;
end

disp(['Stem' ' | ' 'Leaf']);
for i=1:stemNum
    x=stemAndLeafFigure(i).leaf;
    s=size(x,1);
    z=[];
    for j=1:s
        y=sprintf('%2d',x(j));
        z=[z,y];
    end
    disp([' ' num2str(stemAndLeafFigure(i).stem,'%02d') '  |  ' z]);
end


