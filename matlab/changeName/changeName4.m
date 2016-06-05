% 投影后的图片文件格式为pre_num1-num2_suf,而NeuronPreprocessor2.1中能够使用的文件名格式为pre_num_suf(num需为连续的).
% 为了使其能够用于NeuronPreprocessor2.1的投影，本程序将投影后的图片按照num1进行排序，
% 然后按照NeuronPreprocessor2.1所需的命名规则复制到另一个文件夹。
% 需要注意的是，所处理的文件夹内必须都是pre_num1-num2_suf这样命名的文件，而且pre和suf相同。
% 排序是为了处理dir（）读出的文件名中test_2001-2100_stride_100_100_pro.tif排在test_201-300_stride_100_100_pro.tif之前

% clear all;                                          % 这一句不可缺失，不作为函数运行的话,其他程序运行留下的workspace可能会有残留，影响结果。
% clc;

clc;
clear all;

src_file='W:\lsu\TDI072\6-5000\11new\';
dst_file='W:\lsu\TDI072\6-5000\11new\';

file=dir(src_file);
l_file=length(file);
pre='';
suf='_zResample_1_max.tif';

index1=1;
for i=6:1:5000      
    rawName=[pre num2str(i) '-' num2str(i) suf];
    changedName=[num2str(i,'%05d') '.tif'];
    
    tic;
    disp(rawName);
    movefile([src_file rawName],[dst_file changedName]);
%     system(['ren ' rawName ' ' changedName]);
    disp(changedName);
    toc;
    index1=index1+1;
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


    
    

    
    