% 文件夹内图片存放格式：编号-编号+后缀 例：2001-2001_zResample_1_max.tif 编号位数不固定，从1位到n位。后缀固定。例：_zResample_1_max.tif
% 程序目的：从取样后的文件中每隔n张选一张，放进目标文件夹，实现z方向重采样。
% 想法：dir（）读出所有文件名，对每个文件名遍历至第一个‘-’的位置，然后取出编号，存进临时数组Num中，全部完成后，对Num中元素进行隔n选一
% 然后用copyfile（name1，name2）将文件复制。
% function [Num]=pickimage(interval_num,desfile,srcfile)
function [Num]=pickimage(srcfile)
f=dir(srcfile);
l=length(f);
for i=3:l
    temp=f(i).name;
    name_l=length(temp);
    for j=1:name_l
        if(temp(j)=='-')
            break;
        end
    end
    a=temp(1:j-1);
    disp(a);
    Num(i-2)=str2num(a);
end

