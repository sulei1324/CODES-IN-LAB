% ���������ڼ���ļ�����ȱʧ�ļ����䣬Ҫ���ļ������ļ���ͬһ�ֹ���������ǰ׺+���+��׺��
% ��Ҫ��д�ļ�������src_file��ǰ׺pre����׺suf



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
     
% ����������9620���ļ�����ʱ��Ϊ223.743389s

% ����������4800���ļ����޶�ʧ������ʱ��Ϊ25.029074 seconds
