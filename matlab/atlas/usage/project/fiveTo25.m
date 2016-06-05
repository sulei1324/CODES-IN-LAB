clc;
clear all;

src = 'Y:\AppData\ZSQGroup\part3\TDI21301006-1\R\projection-5um\';
zRange = [339, 9218];
thick = 25;
dst = 'W:\xhu\TDI21301006\project_25um\2\';
pre = 'test_';
suf = '_pro.tif';
bits = 16;

for i = zRange(1) : thick : zRange(2)
    tmp_files = {};
    for j = 1 : 5
       tmp_start_slice = i + 5 * (j - 1);
       tmp_end_slice = i + 5 * j - 1;
       if j == 1
           s = tmp_start_slice;
       end
       if tmp_end_slice > zRange(2)
           break;
       end
       e = tmp_end_slice;
       tmp_name = [src pre num2str(tmp_start_slice, '%05d') '-' num2str(tmp_end_slice, '%05d') suf];
       tmp_files{j, 1} =  tmp_name;
    end
    disp(tmp_files);
    out_image_name = [dst 'test_' num2str(s, '%05d') '-' num2str(e, '%05d') '.tif'];
    out_image = uint8(proFunction(tmp_files, bits));
    imwrite(out_image, out_image_name);
    disp(out_image_name);
    if tmp_end_slice > zRange(2)
        break;
    end
end