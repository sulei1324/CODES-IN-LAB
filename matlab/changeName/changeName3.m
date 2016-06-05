% 投影后的图片文件格式为pre_num1-num2_suf,而NeuronPreprocessor2.1中能够使用的文件名格式为pre_num_suf(num需为连续的).
% 为了使其能够用于NeuronPreprocessor2.1的投影，本程序将投影后的图片按照num1进行排序，
% 然后按照NeuronPreprocessor2.1所需的命名规则复制到另一个文件夹。
% 需要注意的是，所处理的文件夹内必须都是pre_num1-num2_suf这样命名的文件，而且pre和suf相同。
% 排序是为了处理dir（）读出的文件名中test_2001-2100_stride_100_100_pro.tif排在test_201-300_stride_100_100_pro.tif之前

% clear all;                                          % 这一句不可缺失，不作为函数运行的话,其他程序运行留下的workspace可能会有残留，影响结果。
% clc;

clc;
clear all;

src_file='G:\sulei\13004\10um\13004_pro_10um\2';
dst_file='G:\sulei\13004\10um\13004_pro_10um\3';


file=dir(src_file);
l_file=length(file);
pre='test_';
suf='python.tif';
con='-';
l_pre=length(pre);
l_suf=length(suf);
for i=3:l_file
    f_name=file(i).name;
    l_fName=length(f_name);
    index_con=strfind(f_name(l_pre+1:end),con);
    l_con=l_pre+index_con;
    f_num=f_name(l_pre+1:l_con-1);
    s_num=f_name(l_con+1:l_fName-l_suf);
    num(i-2,1)=str2num(f_num);
    num(i-2,2)=str2num(s_num);
end
l_num=length(num);

for i=1:l_num
    f_num=num(i,1);
    s_num=num(i,2);
    rawName=[pre num2str(f_num) con num2str(s_num) suf];
    changedName=[num2str(f_num,'%05d') con num2str(s_num,'%05d') '_prj.tif'];
    tic;
    disp(rawName);
    copyfile([src_file '\' rawName],[dst_file '\' changedName]);
    disp(changedName);
    toc;
end




% for i=1:l_num
%     c_num=sorted_num(i);
%     for j=3:l_file
%         f_name=file(j).name;
%         index_con=strfind(f_name(l_pre+1:end),con);
%         l_con=l_pre+index_con;
%         a=num2str(c_num);
%         b=f_name(l_pre+1:l_con-1);
%         if(strcmp(a,b))
%             copyfile([src_file '\' f_name],[dst_file '\' 'test_' num2str(i,'%05d') '.tif']);
%             break;
%         end
%     end
% end


    
    

    
    