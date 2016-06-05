clc;
clear all;

%  ����ԭʼͼƬ�����ļ���λ�� ע�⣺�ļ��е�ַĩβҪȷ����\ ��д����һ���е�''�� 
%  ���� �ļ���λ��Ϊd��src�ļ��� 
%  ����һ��ӦΪ src='D:\src\';
src='I:\process\montage\';
%  ����Ŀ��ͼƬ����ļ���λ�� ע�⣺�ļ��е�ַĩβҪȷ����\ ��д����һ���е�''�� 
%  ���� ���λ��Ϊd��dst�ļ���
%  ����һ��ӦΪ dst='D:\dst\';
dst='I:\process\project\';
%  ����ͼƬ�Ŀ�� ���� 100; ����һ��ӦΪ width=100;
width=20592;
%  ����ͼƬ�ĸ߶� ���� 100; ����һ��ӦΪ height=100;
height=51800;
%  ������Ƭ����ʼ���� ���� 668 ����   һ��ӦΪ startZ=668;
startZ=162;
%  ������Ƭ����ֹ���� ���� 1067 ����һ��ӦΪ endZ=1067;
endZ=167;
%  ����ԭʼͼƬ����ǰ׺ ����ԭʼͼƬ��Ϊtest_01258.tif ǰ��׺�ֱ�λ��ͼƬ��ŵ���λ��������
%  ǰ׺��ָtest_ ��׺��ָ.tif ��д����һ�е�''��
pre='test_';
%  ����ԭʼͼƬ���ĺ�׺
post='_mon.tif';
%  ����ͶӰ�ĺ�ȣ�����ÿ100��ͶӰһ�ţ�����һ��ӦΪstackNum=100
stackNum=3;

zRange=[startZ,endZ];
inImage=uint8(zeros(height,width));
tmpImage=uint8(zeros(height,width));
index=1;
for i=zRange(1):zRange(2)
    if i == zRange(1)
        s = i;
    end
    inImage=imread([src pre num2str(i,'%05d') post]);
    disp(['reading ' src pre num2str(i,'%05d') post]);
    if index == stackNum || i == zRange(2)
        e = i;
        disp([dst pre num2str(s,'%05d') '-' num2str(e,'%05d') post]);
        imwrite(tmpImage, [dst pre num2str(s,'%05d') '-' num2str(e,'%05d') post]);
        index = 1;
        tmpImage=uint8(zeros(height,width));
        s = e + 1;
        continue;
    else
        tmpImage = max(tmpImage, inImage);
    end
    index=index+1;
end
