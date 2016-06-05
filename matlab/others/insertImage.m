% suffix 后缀
function insertImage()
im_name1='Y:\Public\mostgroup\data_us\RV_GFP_preprocess\4224-5501\test_05501_montage.tif';
im_name2='Y:\Public\mostgroup\data_us\RV_GFP_preprocess\4224-5501\test_05587_montage.tif';
pre='test_';
suf='_montage.tif';
srcfile='Y:\Public\mostgroup\data_us\RV_GFP_preprocess\4224-5501';


index_pre=strfind(im_name1,pre)-1;

im1=imread(im_name1);

im2=imread(im_name2);
% im1=rgb2gray(im1);
% im2=rgb2gray(im2);

im1=double(im1);      %数值运算时需要double格式
im2=double(im2);
l_name=length(im_name1);

l_pre=length(pre);
l_suf=length(suf);


num_head=im_name1((l_pre+1+index_pre(1)):(l_name-l_suf));

num_tail=im_name2((l_pre+1+index_pre(1)):(l_name-l_suf));
num_head=str2num(num_head);
num_tail=str2num(num_tail);
num_insert=num_tail-num_head-1;
ratio=num_insert+1;

for i=1:num_insert
    im_insert=im1.*((ratio-i)/ratio)+im2.*(i/ratio);
    im_insert=uint8(im_insert);
    im_num=i+num_head;
    imwrite(im_insert,[srcfile '\' pre num2str(im_num,'%05d') suf]);
end
end


