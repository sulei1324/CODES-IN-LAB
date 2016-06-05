function [output] = sortSingleColumnData(inputXls,whichSheet,columnRange,title)

n=size(title,1);

array=xlsread(inputXls,whichSheet,columnRange);

sortedArray=sortrows(array);

num=size(array);

num=num+1;

for i=1:num
    if(i==1)
        
        disp(['    ' '    ' title]);
        continue;
    end
    disp([num2str(i-1,'%04d') '    ' num2str(array(i-1,1),'%-5d')]);
end

end


