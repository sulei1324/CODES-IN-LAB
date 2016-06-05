function s = mkFiles(dst)

s = 0;

swc0_dst = [dst '\\' 'swc0'];
csv0_dst = [dst '\\' 'csv0'];
swc1_dst = [dst '\\' 'swc1'];
csv1_dst = [dst '\\' 'csv1'];
csv2_dst = [dst '\\' 'csv2'];
if ~exist(swc0_dst, 'dir')
    mkdir(swc0_dst);
end
if ~exist(swc1_dst, 'dir')
    mkdir(swc1_dst);
end
if ~exist(csv0_dst, 'dir')
    mkdir(csv0_dst);
end
if ~exist(csv1_dst, 'dir')
    mkdir(csv1_dst);
end
if ~exist(csv2_dst, 'dir')
    mkdir(csv2_dst);
end

s=1;

end