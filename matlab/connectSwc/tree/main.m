clc;
clear all;

global node_array id_array M t;

M = 100;
node_array = cell(1,M);
id_array = zeros(1,M);
t = tree();
swc = load('G:\sulei\workplace\Swc\res\1.swc');

createTreeAsSwc(swc);
trace();
