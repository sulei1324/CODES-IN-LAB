clc;
clear all;

start_x=-370;
start_y=278;
location={};

for i=1:5
    x=start_x+(40)*(i-1);
    for j=1:11
        y=start_y-(26)*(j-1);
        temp=[x,y];
        location{j,i}=temp;
    end
end

