function readTime()

tic

b=imread('Y:\Public\mostgroup\data_us\RV_GFP_preprocess\4224-5501\test_04951_montage.tif');

a=toc;

disp(a);




% 本地读图  16.7060ｓ
% 服务器读图　66.8517ｓ
