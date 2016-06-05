clc;
clear all;



for i=668:768
    tic;
    I=imread(['Y:\Public\mostgroup\data_us\MBA-GF13004_cut\16-22\test_' num2str(i,'%05d') '_x15560_y_20220_w_3970_h_4716.tif']);
    A(:,:,i)=I(1:1000,1:1000);
    
    toc;
end
