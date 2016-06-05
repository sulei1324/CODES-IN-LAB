clc;
clear all;


%  ����ԭʼͼƬ�����ļ���λ�� ע�⣺�ļ��е�ַĩβҪȷ����\ ��д����һ���е�''�� 
%  ���� �ļ���λ��Ϊd��src�ļ��� 
%  ����һ��ӦΪ src='D:\src\';
src='W:\lsu\movie\11-6movie\hippo\hippo-crop\';
%  ����Ŀ��ͼƬ����ļ���λ�� ע�⣺�ļ��е�ַĩβҪȷ����\ ��д����һ���е�''�� 
%  ���� ���λ��Ϊd��dst�ļ���
%  ����һ��ӦΪ dst='D:\dst\';
dst='W:\lsu\movie\book\part5\hippo_pro2\';
%  ����ͼƬ�Ŀ�� ���� 100; ����һ��ӦΪ width=100;
width=1884;
%  ����ͼƬ�ĸ߶� ���� 100; ����һ��ӦΪ height=100;
height=1452;
%  ����ͶӰ����ʼ���� ���� 668 ����һ��ӦΪ startZ=668;
startZ=668;
%  ����ͶӰ����ֹ���� ���� 1067 ����һ��ӦΪ endZ=1067;
endZ=1067;
%  ����ԭʼͼƬ����ǰ׺ ����ԭʼͼƬ��Ϊtest_01258.tif ǰ��׺�ֱ�λ��ͼƬ��ŵ���λ��������
%  ǰ׺��ָtest_ ��׺��ָ.tif ��д����һ�е�''��
pre='hippo_';
%  ����ԭʼͼƬ���ĺ�׺
post='.tif';
%  ����ͶӰ�ĺ�� ���� 100 ����һ��ӦΪstackNum=100;
stackNum=50;



zRange=[startZ, endZ];
inImage=uint16(zeros(height,width));
tmpImage=uint16(zeros(height,width));
index=1;
for i=zRange(1):zRange(2)
    if i == zRange(1)
        s = i;
    end
    inImage=imread([src pre num2str(i,'%05d') post]);
    disp(['reading ' src pre num2str(i,'%05d') post]);
    if index == stackNum || i == zRange(2)
        e = i;
        disp(['writing ' dst pre num2str(s,'%05d') '-' num2str(e,'%05d') post]);
        imwrite(tmpImage, [dst pre num2str(s,'%05d') '-' num2str(e,'%05d') post]);
        index = 1;
        tmpImage=uint16(zeros(height,width));
        s = e + 1;
        continue;
    else
        tmpImage = max(tmpImage, inImage);
    end
    index=index+1;
end
