clc;

clear all;

h=0;

tic;

for i=1:10000
    tic;
    for j=1:10000
      
        for k=1:10000
            h=h+1;
        end
        
    end
    toc;
end

toc;

disp(h);


% Elapsed time is 0.002913 seconds. 100*100*100 nothing to do

% Elapsed time is 3.709105 seconds. 1000*1000*1000 just add a num

% Elapsed time is 0.003968 seconds. 100*100*100 just add a num