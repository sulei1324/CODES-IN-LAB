clc;
clear all;


for pic_no= 1:1:513
    pic_name = sprintf('hip_%05d', pic_no);
    data = imread('raw.tif', pic_no);
    background = imread('recrop_background.tif',pic_no);
    ker = mean(background(:,:));
    pic_size = size(data);
    ratio = 1./(ker/max(ker));
    data_adj = data;
    for i = 1:1:pic_size(1,1)
        for j = 1:1:pic_size(1,2)
            data_adj(i,j) = data(i,j)*ratio(j);
        end
    end
    imwrite(data_adj,strcat(pic_name,'.bmp'),'bmp');
end
