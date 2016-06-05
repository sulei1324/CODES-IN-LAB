function nnames = getNames(a_src)
axon_files = dir(a_src);
% den_files = dir(d_src);
nnames = {};
for i = 3 : size(axon_files, 1)
   axon_name = axon_files(i, 1).name(1 : end - 4); 
   nnames{size(nnames, 1) + 1, 1} = axon_name;
end
% for i = 3 : size(den_files, 1)
%    den_name = den_files(i, 1).name(1 : end - 4);
%    nnames{size(nnames, 1) + 1, 1} = den_name; 
% end
end