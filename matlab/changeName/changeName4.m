% ͶӰ���ͼƬ�ļ���ʽΪpre_num1-num2_suf,��NeuronPreprocessor2.1���ܹ�ʹ�õ��ļ�����ʽΪpre_num_suf(num��Ϊ������).
% Ϊ��ʹ���ܹ�����NeuronPreprocessor2.1��ͶӰ��������ͶӰ���ͼƬ����num1��������
% Ȼ����NeuronPreprocessor2.1��������������Ƶ���һ���ļ��С�
% ��Ҫע����ǣ���������ļ����ڱ��붼��pre_num1-num2_suf�����������ļ�������pre��suf��ͬ��
% ������Ϊ�˴���dir�����������ļ�����test_2001-2100_stride_100_100_pro.tif����test_201-300_stride_100_100_pro.tif֮ǰ

% clear all;                                          % ��һ�䲻��ȱʧ������Ϊ�������еĻ�,���������������µ�workspace���ܻ��в�����Ӱ������
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


    
    

    
    