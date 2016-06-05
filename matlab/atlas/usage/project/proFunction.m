function img = proFunction(pro_files, bits)
if bits == 8
    tmp_image = imread(pro_files{1, 1});
    image_size = size(tmp_image);
    w = image_size(2);
    h = image_size(1);
    img = uint8(zeros(h, w));
    for i = 1 : size(pro_files, 1)
        if i ~= 1
           tmp_image = imread(pro_files{i, 1}); 
        end
        img = max(tmp_image, img);
    end
else if bits == 16
    tmp_image = uint16(imread(pro_files{1, 1}));
    image_size = size(tmp_image);
    w = image_size(2);
    h = image_size(1);
    img = uint16(zeros(h, w));
    for i = 1 : size(pro_files, 1)
        if i ~= 1
           tmp_image = uint16(imread(pro_files{i, 1})); 
        end
        img = max(tmp_image, img);
    end        
    end
end








end