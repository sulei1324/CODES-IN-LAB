clc;
clear all;

src = 'W:\lsu\TDI072\contour-olfactory bulb\sl\crop\generate\';
dst = 'W:\lsu\TDI072\contour-olfactory bulb\sl\crop\generate_re\';
for i = 1 : 2251
    s_i = num2str(i, '%05d');
    image1 = imread([src s_i '.tif']);
    image2 = uint8(imresize(image1, 0.1));
    imwrite(image2, [dst s_i '.re.tif']);
end