% �ļ�����ͼƬ��Ÿ�ʽ�����-���+��׺ ����2001-2001_zResample_1_max.tif ���λ�����̶�����1λ��nλ����׺�̶�������_zResample_1_max.tif
% ����Ŀ�ģ���ȡ������ļ���ÿ��n��ѡһ�ţ��Ž�Ŀ���ļ��У�ʵ��z�����ز�����
% �뷨��dir�������������ļ�������ÿ���ļ�����������һ����-����λ�ã�Ȼ��ȡ����ţ������ʱ����Num�У�ȫ����ɺ󣬶�Num��Ԫ�ؽ��и�nѡһ
% Ȼ����copyfile��name1��name2�����ļ����ơ�
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

