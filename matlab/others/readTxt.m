clc;

clear all;

f=fopen('1.txt','w');

% A=fscanf(f,'%c');


A='222222';

fwrite(f,A);

% B=char(A);

% B='IIIIII';
% 
% fwrite(f,B);

fclose(f);

