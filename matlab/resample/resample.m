clc;
clear all;

src = 'Y:\Public\mostPreprocess\TDI072\montage\';
dst = 'G:\sulei\TDI072\resample_222\';
pre = 'test_';
post = '_mon.tif';
zRange = [6, 11900];
raw_image = uint8(zeros(35000, 23760));


for i = zRange(1) : 2 : zRange(2)
    if i > 2500
        break;
    end
    image_name = [src pre  num2str(i, '%05d')  post];
    raw_image = imread(image_name);
    tmp_image = imresize(raw_image, 0.15);
    imwrite(tmp_image, [dst pre num2str(i, '%05d') '_res.tif']); 
    disp(image_name);
end

    
