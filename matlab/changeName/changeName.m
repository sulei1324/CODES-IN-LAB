% ͶӰ���ͼƬ�ļ���ʽΪpre_num1-num2_suf,��NeuronPreprocessor2.1���ܹ�ʹ�õ��ļ�����ʽΪpre_num_suf(num��Ϊ������).
% Ϊ��ʹ���ܹ�����NeuronPreprocessor2.1��ͶӰ��������ͶӰ���ͼƬ����num1��������
% Ȼ����NeuronPreprocessor2.1��������������Ƶ���һ���ļ��С�
% ��Ҫע����ǣ���������ļ����ڱ��붼��pre_num1-num2_suf�����������ļ�������pre��suf��ͬ��
% ������Ϊ�˴���dir�����������ļ�����test_2001-2100_stride_100_100_pro.tif����test_201-300_stride_100_100_pro.tif֮ǰ

% clear all;                                          % ��һ�䲻��ȱʧ������Ϊ�������еĻ�,���������������µ�workspace���ܻ��в�����Ӱ������
% clc;

function changeName()
src_file='Y:\Public\mostgroup\data_us\AAV-YFP-project\AAV-YFP_42-3233_project_100um';
dst_file='Y:\Public\mostgroup\data_us\AAV-YFP-project\AAV-YFP_42-3233_project-100um_20x-sample\42-3233_project-100um_rename';


file=dir(src_file);
l_file=length(file);
pre='test_';
suf='_stride_10.tif';
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
        if(strcmp(a,b))
            copyfile([src_file '\' f_name],[dst_file '\' 'test_' num2str(i,'%05d') '.tif']);
            break;
        end
    end
end
end

    
    

    
    