clc;
clear all;
src = 'W:\lsu\TDI072\contour-olfactory bulb\sl\crop\swc\';
files = dir(src);
whole_lines= [];



for i = 1 : size(files, 1)
   if (strcmp(files(i, 1).name , '.')) || (strcmp(files(i, 1).name, '..'))
       continue;
   end
   swc_name = files(i, 1).name;
   swc = load([src swc_name]);
   disp(swc_name);
   this_swc_lines = divide2lines(swc);
   whole_lines = [whole_lines; this_swc_lines]; 
end
