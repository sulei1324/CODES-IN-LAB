% clc;
% clear all; 
% src = 'W:\xhu\test\3\syn_diff_points.tif';
% dir ='W:\xhu\test\3\syn_diff_100\'; 
% pointnumber=100;        %每一层点集的数量 
% for i=1:528 
%        k=0; 
%        l=1; 
%        I=double(imread(src, i)); 
%        if max(max(I))==0; 
%                temp=zeros(size(I)); 
%                imwrite(uint8(temp),[dir    num2str(i,'%05d') '.tif']);     
%                disp(['-------this zero------',num2str(i)]); 
%        else 
%                lab_edge=double(edge(I,'canny')); 
%                num=sum(sum(lab_edge)); 
%                if num<=pointnumber 
%                        rand_box=randperm(num); 
%                        rand_box=sort(rand_box(1:num)); 
%                else 
%                        rand_box=randperm(num); 
%                        rand_box=sort(rand_box(1:pointnumber));           
%                end 
%                        [p, q]=size(I); 
%                        temp=zeros(size(I)); 
%                for m=1:p 
%                        for n=1:q 
%                                if lab_edge(m,n)==1 
%                                        k=k+1; 
%                                        if l<pointnumber+1 && k==rand_box(1,l)   
%                                                temp(m,n)=255; 
%                                                l=l+1; 
%                                        end 
%                                end 
%                        end 
%                end 
%                imwrite(uint8(temp),[dir    num2str(i,'%05d') '.tif']);   
%                disp(['-------this non-------------zero------',num2str(i)]); 
%        end 
% end