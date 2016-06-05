% ½«MBA-MC14278_xxxxx_CH1.txt¸Ä³Étemp_xxxxx.tif


% function changeName2()

clc;

clear all;

src_file='Y:\Public\mostzhangyalun\sulei\matlab\test\changeNameTest';
% dst_file='Y:\Public\mostzhangyalun\sulei\matlab\test_dst\changeNameTest';
cd(src_file);


file=dir(src_file);
l_file=length(file);
pre='MBA-MC14278_';
suf='_CH1.txt';
% con='-';
l_pre=length(pre);
l_suf=length(suf);
for i=3:l_file
    f_name=file(i).name;
%     index_con=strfind(f_name(l_pre+1:end),con);
%     l_con=l_pre+index_con;
    f_num=f_name(l_pre+1:l_pre+4);
    f_num=str2num(f_num);
    num(i-2)=f_num;
%     copyfile([src_file '\' f_name],[dst_file '\' 'temp_' num2str(f_num,'%05d') '.tif']);
end



sorted_num=sort(num);
l_num=length(sorted_num);


for i=1:l_num
    c_num=sorted_num(i);
    for j=3:l_file
        f_name=file(j).name;
%         index_con=strfind(f_name(l_pre+1:end),con);
%         l_con=l_pre+index_con;
%         a=num2str(c_num);
        b=f_name(l_pre+1:l_pre+4);
        b=str2num(b);
        disp(c_num);
        disp(b);
        if(c_num==b)
%             copyfile([src_file '\' f_name],[dst_file '\' 'temp_' num2str(i,'%05d') '.txt']);
            system(['ren ' f_name ' ' pre num2str(c_num,'%05d') suf]);
            disp(i);
            break;
        end
    end
end
% end

    
    

    
    