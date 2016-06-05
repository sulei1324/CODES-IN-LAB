clc;
clear all;


%  �����ز����ı��������� 0.3 ����һ��ӦΪ resize_ratio=0.3
resize_ratio = 0.06;
%  ������Ƭ����ʼ���� ���� 668 ����һ��ӦΪ startZ=668;
startZ = 943;
%  ������Ƭ����ֹ���� ���� 1067 ����һ��ӦΪ endZ=1067;
endZ = 946;
%  ����ԭʼͼƬ�����ļ���λ�� ע�⣺�ļ��е�ַĩβҪȷ����\ ��д����һ���е�''�� 
%  ���� �ļ���λ��Ϊd��src�ļ��� 
%  ����һ��ӦΪ src='D:\src\';
src='I:\process\montage\';
%  ����Ŀ��ͼƬ����ļ���λ�� ע�⣺�ļ��е�ַĩβҪȷ����\ ��д����һ���е�''�� 
%  ���� ���λ��Ϊd��dst�ļ���
%  ����һ��ӦΪ dst='D:\dst\';
dst='I:\process\resize\';
%  ����ԭʼͼƬ����ǰ׺ ����ԭʼͼƬ��Ϊtest_01258.tif ǰ��׺�ֱ�λ��ͼƬ��ŵ���λ��������
%  ǰ׺��ָtest_ ��׺��ָ.tif ��д����һ�е�''��
pre='test_';
%  ����ԭʼͼƬ���ĺ�׺
post='_mon.tif';

tmpImage=imread([src pre num2str(startZ,'%05d') post]);
[rawImageHeight,rawImageWidth]=size(tmpImage);
clear tmpImage;
wPre='test_';
wPost='.tif';
inImage=uint8(zeros(rawImageHeight,rawImageWidth));
for i=startZ:endZ
    inImage=imread([src pre num2str(i,'%05d') post]);
    disp(['reading ' num2str(i,'%05d') ' image']);
    outImage=imresize(inImage, resize_ratio);
    outImage = uint8(outImage);
    disp(['writing ' num2str(i,'%05d') ' image'])
    imwrite(outImage,[dst wPre num2str(i,'%05d') '_res' wPost]);
end

    
