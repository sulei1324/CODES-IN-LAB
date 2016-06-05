function allSwc = MergeTwoSwc(swc1,swc2)
allSwc = [swc1;swc2];
allSwc(:,1) = 1:size(allSwc,1);
for i = size(swc1,1)+1 : size(allSwc, 1)
    if allSwc(i,7) > -1
        allSwc(i,7) = allSwc(i,7) + size(swc1,1);
    end
end