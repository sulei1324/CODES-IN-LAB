
clear all;
clc;


% function findLostNum()

src_file='Y:\Public\mostgroup\data_us\AAV-YFP-project\uni_42-3233';
pre='test_';
suf='_montange.tif';
l_p=length(pre);
l_s=length(suf);
file=dir(src_file);
l_file=length(file)-2;

for i=3:length(file)
    f_name=file(i).name;
    l_f_name=length(f_name);
%   s_num=file(i).name(l_p+1:l_s-1);    
    s_num=f_name(l_p+1:l_f_name-l_s+1);

    num=str2num(s_num);
    exitNumArray(i-2)=num;
end

totalNum=length(exitNumArray);
startNum=exitNumArray(1);
endNum=exitNumArray(totalNum);

findFlag=0;
lost=0;
for j=startNum:endNum
    
    for k=1:totalNum
        if(j==exitNumArray(k))
            findFlag=1;
            break;
        else
            findFlag=0;
        end
    end
    if(~(findFlag))
        lost=lost+1;
        lostNumArray(lost)=j;
    end
    
end

if(lost==0)
	disp('no lost.');

else
	if(lost==1);
    else
        s=lostNumArray(1)
		for i=1:(lost-1)
            if((lostNumArray(i+1)-lostNumArray(i))==1) continue;
            else
                e=lostNumArray(i);
                s=lostNumArray(i+1);
                disp(s);
                disp(e);
                
			



% end
     

