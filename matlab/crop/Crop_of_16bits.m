clc;
clear all;


%  ������Ƭ��ԭʼͼƬ�е���ʼx���� ���� 1111 ����һ��ӦΪ startX=1111;
startX=17803;
%  ������Ƭ��ԭʼͼƬ�е���ʼy���� ���� 1111 ����һ��ӦΪ startY=1111;
startY=19603;
%  ������Ƭ�Ŀ�� ���� 100; ����һ��ӦΪ width=100;
width=508;
%  ������Ƭ�ĸ߶� ���� 100; ����һ��ӦΪ height=100;
height=499;
%  ������Ƭ����ʼ���� ���� 668 ����һ��ӦΪ startZ=668;
startZ=3333;
%  ������Ƭ����ֹ���� ���� 1067 ����һ��ӦΪ endZ=1067;
endZ=22222;
%  ����ԭʼͼƬ�����ļ���λ�� ע�⣺�ļ��е�ַĩβҪȷ����\ ��д����һ���е�''�� 
%  ���� �ļ���λ��Ϊd��src�ļ��� 
%  ����һ��ӦΪ src='D:\src\';
src='Y:\Public\mostPreprocess\TDI072\montage\';
%  ����Ŀ��ͼƬ����ļ���λ�� ע�⣺�ļ��е�ַĩβҪȷ����\ ��д����һ���е�''�� 
%  ���� ���λ��Ϊd��dst�ļ���
%  ����һ��ӦΪ dst='D:\dst\';
dst='G:\sulei\workplace\Swc\test2\';
%  ����ԭʼͼƬ����ǰ׺ ����ԭʼͼƬ��Ϊtest_01258.tif ǰ��׺�ֱ�λ��ͼƬ��ŵ���λ��������
%  ǰ׺��ָtest_ ��׺��ָ.tif ��д����һ�е�''��
pre='test_';
%  ����ԭʼͼƬ���ĺ�׺
post='_mon.tif';
wPre='test_';
wPost='_crop.tif';



tmpImage=imread([src pre num2str(startZ,'%05d') post]);
[rawImageHeight,rawImageWidth]=size(tmpImage);
clear tmpImage;
wMid=['_x' num2str(startX) '_y' num2str(startY) '_w' num2str(width) '_h' num2str(height)];
inImage=uint16(zeros(rawImageHeight,rawImageWidth));
outImage=uint16(zeros(height,width));
for i=startZ:endZ
    inImage=imread([src pre num2str(i,'%05d') post]);
    disp(['reading ' num2str(i,'%05d') ' image']);
    outImage=inImage(startY:startY+height-1,startX:startX+width-1);
    disp(['writing ' num2str(i,'%05d') ' image'])
    imwrite(outImage,[dst wPre num2str(i,'%05d') wMid wPost]);
end

    
