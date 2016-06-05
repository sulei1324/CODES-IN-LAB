clc;
clear all;

src = 'Y:\Public\mostPreprocess\TDI21301003\montage\';
dst = 'G:\sulei\TDI21301002\resample\';
pre = 'test_';
post = '_mon.tif';
zRange = [47, 600];

for i = zRange(1) : zRange(2)
    image_name = [src pre  num2str(i, '%05d')  post];
    if i == 1270
        continue;       
    end
    if i == 47
        raw_image = uint16(zeros(35000, 23400));
    else if i == 1271
            raw_image = uint16(zeros(18200, 23400));
        end
    end
    raw_image = imread(image_name);
    tmp_image = imresize(raw_image, 0.1);
    imwrite(tmp_image, [dst pre num2str(i, '%05d') '_res.tif']); 
    disp(image_name);
end

    
