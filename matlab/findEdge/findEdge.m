% ������Ѱ�ұ߽�   ��������Ѱ�ұ߽磨���� ʱ���ٶȶԱ�


% function [edge]=findEdge(image_in,m,n)


% clear all;
% clc;
function findEdge()

startName='H:\sulei\��������\test_05587_montage_edge.tif';
image_in=imread(startName);
image_in=im2bw(image_in);
[m,n]=size(image_in);
edgePointNum=0;
edge={};

imwrite(image_in,'H:\sulei\��������\test_05587_montage_bw.tif')


for i=1:m
    for j=1:n
        if(image_in(i,j)==1)
            if(image_in(i-1,j-1)==0|image_in(i-1,j)==0|image_in(i-1,j+1)==0|image_in(i,j-1)==0|image_in(i,j+1)==0|image_in(i+1,j-1)==0|image_in(i+1,j)==0|image_in(i+1,j+1)==0)
                edgePointNum=edgePointNum+1;
                edge(edgePointNum)={[i,j]};
            end
        end
    end
end

outImage=zeros(m,n);
for i=1:edgePointNum
    outImage(edge{i}(1),edge{i}(2))=1;
end

imshow(outImage);
imwrite(outImage,'H:\sulei\��������\test_05587_montage_findEdge.tif')

end
   
                

