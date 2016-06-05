% 本程序用于检测文件夹中缺失文件区间，要求：文件夹中文件以同一种规则命名，前缀+序号+后缀。
% 需要填写文件夹名称src_file，前缀pre，后缀suf



clear all;
clc;


% function findLostNum()
tic
src_file='X:\RawData\TDI\TDI11302020\R';
pre='';
suf='.finish';
l_p=length(pre);
l_s=length(suf);
file=dir(src_file);
l_file=length(file)-2;

for i=3:length(file)
    f_name=file(i).name;
    if(strcmp(f_name,'new.finish'))
        continue;
    end
    l_f_name=length(f_name);
%   s_num=file(i).name(l_p+1:l_s-1);    
    s_num=f_name(l_p+1:l_f_name-l_s);

    num=str2num(s_num);
    exitNumArray(i-2)=num;
end

totalNum=length(exitNumArray);
startNum=exitNumArray(1);
endNum=exitNumArray(totalNum);

findFlag=0;
lost=0;
for j=startNum:1:endNum
    
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
    l_start=lostNumArray(1);
    l_end=lostNumArray(1);
	if(lost==1)
        s_e=['Only one file is lost: ' num2str(l_start,'%05d')];
		disp(s_e);
	else
		for i=1:(lost-1)
            if((lostNumArray(i+1)-lostNumArray(i))==1) ;
            else
                l_end=lostNumArray(i);
                s_e=['Lost File Area is ' num2str(l_start,'%05d') '--' num2str(l_end,'%05d')];
                disp(s_e);
                l_start=lostNumArray(i+1);
            end
            if(i==lost-1)
                l_end=lostNumArray(i+1);
                s_e=['Lost File Area is ' num2str(l_start,'%05d') '--' num2str(l_end,'%05d')];
                disp(s_e);
            end
        end
    end
end
toc
			



% end
     
% 检测服务器上9620个文件，总时间为223.743389s

% 检测服务器上4800个文件（无丢失），总时间为25.029074 seconds
