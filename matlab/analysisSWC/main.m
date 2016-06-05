clc;
clear all;

swc = load('G:\sulei\SVN\BigMostBrain\BigMostViewer\manual\TDI11107005Z=1925-2024.swc');
% branch_nums = getBranchNum(swc);

lines = divide2lines(lines);
lengths = countLength(lines);
plot(lengths);
% ROTVolumes = getROTVolume(lines);
