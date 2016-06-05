clc;
clear all;

%  ����ԭʼͼƬ�����ļ���λ�� ע�⣺�ļ��е�ַĩβҪȷ����\ ��д����һ���е�''�� 
%  ���� �ļ���λ��Ϊd��src�ļ��� 
%  ����һ��ӦΪ src='D:\src\';
src = 'I:\process\raw\';
%  ����Ŀ��ͼƬ����ļ���λ�� ע�⣺�ļ��е�ַĩβҪȷ����\ ��д����һ���е�''�� 
%  ���� ���λ��Ϊd��dst�ļ���
%  ����һ��ӦΪ dst='D:\dst\';
dst = 'I:\process\montage\';
%  ������Ƭ����ʼ���� ���� 668 ����   һ��ӦΪ startZ=668;
start_serial = 162;
%  ������Ƭ����ֹ���� ���� 1067 ����һ��ӦΪ endZ=1067;
end_serial = 167;
%  ����ԭʼͼƬ����ǰ׺ ����ԭʼͼƬ��Ϊtest_01258.tif ǰ��׺�ֱ�λ��ͼƬ��ŵ���λ��������
%  ǰ׺��ָtest_ ��׺��ָ.tif ��д����һ�е�''��
pre = 'test__';
%  ����ԭʼͼƬ���ĺ�׺
post = '.png';
%  ����֡ͼ�����ʼ����ֹ��xy���
x_beg = 40;
y_beg = 31;
x_end = 55;
y_end = 67;
%  ����֡ͼ��Ŀ��
block_width = 1287;
%  ����֡ͼ��ĸ߶�
block_height = 1400;





whole_image = zeros(block_height * (y_end - y_beg + 1), block_width * (x_end - x_beg + 1));
whole_image = uint8(whole_image);
for i = start_serial : end_serial
   serial_src = [src num2str(i, '%05d') '\'];
   dst_image_name = [dst 'test_' num2str(i, '%05d') '_mon.tif'];
   disp(serial_src);
   for j = x_beg : x_end
       for k = y_beg : y_end
           image_name = [serial_src pre num2str(i, '%05d') '_' num2str(j, '%02d') '_' num2str(k, '%02d') post];
           disp(image_name);
           block_image = imread(image_name);
           block_image = block_image(:, end: -1 :1);           
           whole_image((k-y_beg) * block_height + 1 : (k - y_beg + 1) *block_height, (j-x_beg) * block_width + 1 : (j-x_beg + 1) *block_width) = block_image(:, :);                 
       end
   end
   imwrite(whole_image, dst_image_name);
end

