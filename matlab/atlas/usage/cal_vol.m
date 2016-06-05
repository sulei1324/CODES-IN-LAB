clc;
clear all;

atlas = uint32(zeros(320, 456, 528));
atlas_tag = [];

for i = 1 : 528
    atlas(:, : , i) = imread('W:\lsu\registration\AllenAtlas.tif', i);
    tmp1 = atlas(:, :, i);
    tmp2 = tmp1(:);
    tmp3 = unique(tmp2, 'rows');
    atlas_tag = [atlas_tag; tmp3];
    atlas_tag = unique(atlas_tag, 'rows');
end

atlas_volume = zeros(size(atlas_tag, 1), 1);
for i = 1 : 528
    disp((i / 528 * 100));
    atlas(:, : , i) = imread('W:\lsu\registration\AllenAtlas.tif', i);
    tmp1 = atlas(:, :, i);
    tmp2 = tmp1(:);
    tmp3 = unique(tmp2, 'rows');
    for j = 1 : size(tmp3, 1)
        tag_id = tmp3(j);
        tag_index = find(tmp2 == tag_id);
        tag_num = size(tag_index, 1);
        l = find(atlas_tag == tag_id);
        atlas_volume(l, 1) = atlas_volume(l, 1) + tag_num;
    end
end

atlas_id_v = zeros(size(atlas_tag, 1), 2);
atlas_id_v(:, 1) = atlas_tag(:, 1);
atlas_id_v(:, 2) = atlas_volume(:, 1);

save('id_v_25um3.mat', 'atlas_id_v');



    