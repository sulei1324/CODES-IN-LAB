%%
clc;
clear all
%trace without cross analysization

load  Y:\Public\mostgroup\data_us\MBA-GF13004_cut\neutron\repair\test.txt
str = 'Y:\Public\mostgroup\data_us\MBA-GF13004_cut\48';
des = 'Y:\Public\mostzhangyalun\sulei\matlab\test_dst\otherTest\';

tic
Image_stack=dir(str);
a = imfinfo([str '\' Image_stack(3).name]);
x = a.Width;
y = a.Height;
z = size(Image_stack,1)-2;
origImg = zeros(y,x,z);
markImg = zeros(y,x,z);
 for i = 1 :  z
     i
     origImg(:,:,i) = (double(imread([str '\' Image_stack(i+2).name])));%uint8
     clc
 end
 toc
 
 
 tic
 cell_rad = 7;
 xyz=(round(test(:,3:5)));
 r=size(xyz,1);
max_xyz = max(xyz)
 
 k=r;
 for j = 1:r
     temp_y = round(xyz(j,1)*10/3);
     temp_x = round(xyz(j,2)*10/3);
     temp_z = round(xyz(j,3));
     xyz(j,1)=temp_y;
     xyz(j,2)=temp_x;
     xyz(j,3)=temp_z;
     if(j~=1)
         dis_x=abs(temp_x-last_temp_x);
         dis_y=abs(temp_y-last_temp_y);
         dis_z=abs(temp_z-last_temp_z);
         if(dis_x<60&&dis_y<60&&dis_z<60)
             for temp_cellz=min(last_temp_z,temp_z):15:max(last_temp_z,temp_z)
                 for temp_celly=min(last_temp_y,temp_y):15:max(last_temp_y,temp_y)
                     for temp_cellx=min(last_temp_x,temp_x):15:max(last_temp_x,temp_x)
                         k=k+1;
                         xyz(k,1)=temp_celly;
                         xyz(k,2)=temp_cellx;
                         xyz(k,3)=temp_cellz;
                     end
                 end
             end
         end                         
     end
     last_temp_x = temp_x;
     last_temp_y = temp_y;
     last_temp_z = temp_z;
 end
 
 max_xyz = max(xyz)
 
 for jj = 1:k
     temp_y = xyz(jj,1);
     temp_x = xyz(jj,2);
     temp_z = xyz(jj,3);
     if(temp_x>cell_rad&&temp_x<(y-cell_rad)&&temp_y>cell_rad&&temp_y<(x-cell_rad)&&temp_z>cell_rad&&temp_z<(z-cell_rad))
         for cellz=temp_z-cell_rad:temp_z+cell_rad
             for celly=temp_y-cell_rad:temp_y+cell_rad
                 for cellx=temp_x-cell_rad:temp_x+cell_rad
                     markImg(cellx,celly,cellz) = 1;
                 end
             end
         end            
     end
     
 end
 toc
 

 
 tic
 for imgz=1:z
     for imgy=1:x
         for imgx=1:y
             if(markImg(imgx,imgy,imgz)~=1)
                 origImg(imgx,imgy,imgz)=origImg(imgx,imgy,imgz)*0.1;
             end
         end
     end
     disp([num2str(imgz,'%05d')])
 end
 toc
 
origImg=uint8(origImg);


tic
for i=1:z
    imwrite(origImg(:,:,i),[des num2str(i,'%05d') '.tif']);
end
toc