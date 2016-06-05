clc;
clear all;

src = 'Y:\Public\mostPreprocess\TDI11301005\green\projection\';
dst = 'W:\rguo\TDI11301005-500um\';

all_files = dir(src);
l = size(all_files, 1);

index = 1;
for i = 3 : 5 : l
    tic;
    s = i;
    e = i + 4;
    if e > l
        e = l;
    end
    tmpImage = uint16(zeros(36400, 23400));
    for j = s : e        
        if strcmp(all_files(j, 1).name, 'thumb.db')
            continue;
        end        
        this_image_name = all_files(j, 1).name;
        disp(['reading: ' src this_image_name]);
        this_image = imread([src this_image_name]);
        tmpImage = max(this_image, tmpImage);
    end
    disp(['writing: ' dst num2str(index, '%02d') '.tif']);
    imwrite(tmpImage, [dst num2str(index, '%02d') '.tif']);
    index = index + 1;
    toc;
end

% imwrite(tmpImage, [dst 'all_project.tif']);