clc;
clear all;

% f=fopen('2.tif');
% b=fread(f,'uint8');
% fclose(f);

% function readTifWandH()

% tic;
% a=imfinfo('C:\Users\Â¦Ñô\Desktop\test_02290_adjust.tif');
% toc;
% tic;
% a = imread('C:\Users\Â¦Ñô\Desktop\test_02290_adjust.tif');
% disp(size(a));
% toc;

tic;

f=fopen('C:\Users\Â¦Ñô\Desktop\test_02290_adjust.tif');
a=fread(f,[8,1],'uint8');


high2low=1;
low2high=0;

if(a(1)==73)
    read_dir=high2low;
else
    read_dir=low2high;
end

if(read_dir)
    attr_pos=a(8)*(16^6)+a(7)*(16^4)+a(6)*(16^2)+a(5)*(16^0)+1;
else
    attr_pos=a(5)*(16^6)+a(6)*(16^4)+a(7)*(16^2)+a(8)*(16^0)+1;
end

% disp(attr_pos);

fseek(f,(attr_pos-9),0);

attr_num_raw_data=fread(f,[2,1],'uint8');

% disp(attr_num_raw_data);



if(read_dir)
    attr_num=attr_num_raw_data(2)*(16^2)+attr_num_raw_data(1);
else
    attr_num=attr_num_raw_data(1)*(16^2)+attr_num_raw_data(2);
end

width=0;
height=0;

attr_raw_data=fread(f,[attr_num*12,1],'uint8');

for i=1:attr_num
    attr_i_pos=1+12*(i-1);
    if(read_dir)
        if((attr_raw_data(attr_i_pos+1)*(16^2)+attr_raw_data(attr_i_pos))==256)
            width=attr_raw_data(attr_i_pos+11)*(16^6)+...
                attr_raw_data(attr_i_pos+10)*(16^4)+attr_raw_data(attr_i_pos+9)*(16^2)...
                +attr_raw_data(attr_i_pos+8)*(16^0);
        end
        if((attr_raw_data(attr_i_pos+1)*(16^2)+attr_raw_data(attr_i_pos))==257)
            height=attr_raw_data(attr_i_pos+11)*(16^6)+...
                attr_raw_data(attr_i_pos+10)*(16^4)+attr_raw_data(attr_i_pos+9)*(16^2)...
                +attr_raw_data(attr_i_pos+8)*(16^0);
        end
    else
        if((attr_raw_data(attr_i_pos)*(16^2)+attr_raw_data(attr_i_pos+1))==256)
            width=attr_raw_data(attr_i_pos+8)*(16^6)+...
                attr_raw_data(attr_i_pos+9)*(16j^4)+attr_raw_data(attr_i_pos+10)*(16^2)...
                +attr_raw_data(attr_i_pos+11)*(16^0);
        end
        if((attr_raw_data(attr_i_pos)*(16^2)+attr_raw_data(attr_i_pos+1))==257)
            height=attr_raw_data(attr_i_pos+8)*(16^6)+...
                attr_raw_data(attr_i_pos+9)*(16^4)+attr_raw_data(attr_i_pos+10)*(16^2)...
                +attr_raw_data(attr_i_pos+11)*(16^0); 
        end
    end
%     if((width~=0)&(height~=0))
%         break;
%     end
end

toc;

i_size=[width,height];
disp(i_size);

% end
 
%  Elapsed time is 0.001788 seconds. 23400*36400µÄÍ¼Æ¬

%  Elapsed time is 0.001768 seconds. 1602*956µÄÍ¼Æ¬
            
    
