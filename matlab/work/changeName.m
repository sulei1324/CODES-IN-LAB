% 排序是为了处理test_18-100.tiff排在test_1828-2000.tif之后

clc;
src_file='D:\MATLAB\work\test';
dst_file='D:\MATLAB\work\result';


file=dir(src_file);
l_file=length(file);
pre='test_';
suf='_pro.jpg';
con='-';
l_pre=length(pre);
l_suf=length(suf);
for i=3:l_file
    f_name=file(i).name;
    index_con=strfind(f_name(l_pre+1:end),con);
    l_con=l_pre+index_con;
    f_num=f_name(l_pre+1:l_con-1);
    num(i-2)=str2num(f_num);
end
sorted_num=sort(num);
l_num=length(sorted_num);



for i=1:l_num
    c_num=sorted_num(i);
    for j=3:l_file
        f_name=file(j).name;
        index_con=strfind(f_name(l_pre+1:end),con);
        l_con=l_pre+index_con;
        a=num2str(c_num);
        b=f_name(l_pre+1:l_con-1);
        disp(a);
        disp(b);
        if(strcmp(a,b))
            copyfile([src_file '\' f_name],[dst_file '/' 'test_' num2str(i,'%05d') '.jpg'])
            break;
        end
    end
end

    
    

    
    