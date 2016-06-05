clc;
clear all;

src = 'W:\lsu\registration\TDI072\res\';
mat1 = load([src 'affine0GenericAffine.mat']);
mat2 = load([src 'syn0GenericAffine.mat']);

mat11 = zeros(4, 4);
mat22 = zeros(4, 4);
for i = 1 : size(mat1.AffineTransform_double_3_3)
   if i == 1
       r_i = 0;
   end
   c_i = mod(i, 3);
   if c_i == 0
       c_i = 3;
   end
   if  mod(i, 3) == 1
       r_i = r_i + 1;
   end
   mat11(r_i, c_i) = mat1.AffineTransform_double_3_3(i);
    
    
end
mat11(4, 4) = 1;
centerShift1 = diag([1, 1, 1, 1]);
for i = 1 : size(mat1.fixed)
    centerShift1(4, i) = - mat1.fixed(i);
end






for i = 1 : size(mat2.AffineTransform_float_3_3)
   if i == 1
       r_i = 0;
   end
   c_i = mod(i, 3);
   if c_i == 0
       c_i = 3;
   end
   if  mod(i, 3) == 1
       r_i = r_i + 1;
   end
   mat22(r_i, c_i) = mat2.AffineTransform_float_3_3(i);
    
    
end
mat22(4, 4) = 1;

w = 23760;
h = 35000;
axon_swcs_src = 'W:\lsu\TDI072\figure\3\all_cell\3\axon';
den_swc_src = 'W:\lsu\TDI072\figure\3\all_cell\3\den';
dst = 'W:\lsu\registration\TDI072\swcTrans';
axon_files = dir(axon_swcs_src);
den_file = dir(den_swc_src);
shift_z = 0;

% for i = 3 : size(axon_files)
%    a_axon_name = axon_files(i).name;
%    disp(a_axon_name);
%    a_swc = load([axon_swcs_src '\' a_axon_name]);
%    a_axon_lines = getLines(a_swc);
%    for j = 1 : size(a_axon_lines, 1)
%       a_axon_a_line = a_axon_lines{j};
%       a_axon_a_line(:, 5) = 475 - (a_axon_a_line(:, 5) - shift_z) / 10;
%       a_axon_a_line(:, 5) = a_axon_a_line(:, 5) / 2.5;
%       t_y = a_axon_a_line(:, 4);
%       a_axon_a_line(:, 4) = a_axon_a_line(:, 3) / 25;
%       a_axon_a_line(:, 3) = (h * 0.3 - t_y) / 25;
%       for k = 1 : size(a_axon_a_line, 1)
%          t_xyza = [a_axon_a_line(k, 3 : 5), 1];
%          r_xyza = t_xyza * mat11 * mat22;
%          a_axon_a_line(k, 3 : 5) = r_xyza(1 : 3);
%       end
%       dlmwrite([dst '\t_' num2str(j, '%03d') a_axon_name],a_axon_a_line,'delimiter',' ',  'newline','pc');
%    end
% end

for i = 3 : size(axon_files)
   a_axon_name = axon_files(i).name;
   disp(a_axon_name);
   a_swc = load([axon_swcs_src '\' a_axon_name]);
   a_swc(:, 5) = (a_swc(:, 5) - shift_z) / 25;
%    a_swc(:, 5) = a_swc(:, 5) / 2.5;
   t_y = a_swc(:, 4);
   a_swc(:, 4) = a_swc(:, 3) / 25;
   a_swc(:, 3) = (h * 0.3 - t_y) / 25;
   for k = 1 : size(a_swc, 1)
      t_xyza = [a_swc(k, 3 : 5), 1];
      r_xyza = t_xyza * mat11 * mat22;
      a_swc(k, 3 : 5) = r_xyza(1 : 3);
   end
   dlmwrite([dst '\t_' a_axon_name],a_swc,'delimiter',' ',  'newline','pc');
   
end





