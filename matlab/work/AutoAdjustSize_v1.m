%%
clc;
clear all
load  C:\Users\most\Desktop\XY.txt
% load  G:\lishiwei\AdjustSize\Section.txt
%AutoAdjustSize
Src='Y:\Public\mostgroup\data_us\AAV-YFP_preprocess\';
Dst='YY:\Public\mostgroup\data_us\AAV-YFP-project\uni_42-3233';
Ipr='test_';
Ipt='_montage.tif';
tile_height=1400;
tile_width=1300;
Section=XY(:,1:2);
[m,n]=size(Section);
S=reshape(Section,1,m*n);
Xmax=max(max(XY(:,3:4)));
Ymax=max(max(XY(:,5:6)));
Xmin=min(min(XY(:,3:4)));  
Ymin=min(min(XY(:,5:6)));
Max_height=Xmax-Xmin+1;
Max_width=Ymax-Ymin+1;
buffersize = [Max_height*tile_height,Max_width*tile_width];
sectionBuffer = ones(buffersize, 'uint8') * 0 ;%Black 
%
Ad=dir([Src]);
N=size(Ad,1);
len=length(Ipr);








for k=3:length(Ad) %start from 106 not 105,end with 
    tic
    fileName=Ad(k).name;
    Num=str2num(fileName(len+1:len+5));  
    for index=1:m
        if(Section(index,1)<=Num<=Section(index,2))
            row=index;
        end
    end
    
    
    
%     S_new=[S Num];
%     S_new_sort=sort(S_new);
%     index=find(S_new_sort==Num);
%     if (size(index,2)==3)
%         S_new_one=sort(S);
%         index_new=find(S_new_one==Num);
%         row=round(index_new(1,1)/2);
%     elseif (size(index,2)==1)
%         index_r=S_new_sort(index-1);
%         index_l=S_new_sort(index+1);
%         indexl1=find(Section==index_l);
% %         indexr1=find(Section==index_r);
%         if(indexl1>m)
%         row=indexl1-m;
%         else
%             row=indexl1;
%         end
% %    和边界相等的情况
%     elseif (size(index,2)==2)
%          index_one=S_new_sort(index(1,1));
%         pp=find(Section==index_one);
%         if(pp>m)
%         row=pp-m;
%         else
%             row=pp;
%         end
%          index_two=S_new_sort(index-1);%101,314
%         index_thr=S_new_sort(index+1);%314,315
%         index_two_new=find(Section==index_two(1,1));
%         index_thr_new=find(Section==index_thr(1,2));
%         if(index_two_new>m)
%         row_two=index_two_new-m;
%         else
%             row_two=index_two_new;
%         end
%         if(index_thr_new>m)
%         row_thr=index_thr_new-m;
%         else
%             row_thr=index_thr_new;
%         end
%         if(row==index_two_new)
%             index_r=index_two(1,1);
%             index_l=index_two(1,2);
%         else(row==index_thr_new)
%              index_one_new=index_thr_new;
%              index_r=index_thr(1,1);
%              index_l=index_two(1,2);
%         end
%       
%     end
%     Adujust(row,index_r,index_l)  
    Xstrat=XY(row,3)-Xmin;
%     Xend=XY(row,4)-Xmin;
    Xend=XY(row,4)-Xmin+1;
    Ystrat=XY(row,5)-Ymin;
    Yend=XY(row,6)-Ymin+1;
    I = imread([Src Ad(k).name]);
    sectionBuffer(Xstrat*tile_height+1:Xend*tile_height,Ystrat*tile_width+1:Yend*tile_width) = I(:,:);
%     Buffer1=[ sectionBuffer zeroBuffer];
%     sectionBuffer=Buffer1(:,1:18180);
    %buffersize2 = size(sectionBuffer(xstart*xp:xend*xp-1,ystart*yp:yend*yp-1));
%     imrotate(sectionBuffer,180);
    imwrite(sectionBuffer,[Dst Ad(k).name]);
    disp(['------' num2str(Num,'%05d') '------' ]);
    toc
 end

    
