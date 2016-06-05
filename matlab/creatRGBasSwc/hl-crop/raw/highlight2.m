% function highlight2()
clc;
clear all;
tic;
width=3840;
height=2344;
zRange=[1,700];
level=zRange(2)-zRange(1)+1;

src=('Y:\Public\mostgroup\data_us\MBA-GF13004_cut\neutron\repair\48\48_sub\');
dst=('Y:\Public\mostzhangyalun\sulei\matlab\test_dst\48\');
pre='48';
suf='.tif';

Ratio=0.1;
R=5;
Image=zeros(height,width,level);

Image=zeros(height,width,level);
tmpImage=zeros(height,width,level);

for i=zRange(1):zRange(2)
%     tmpImage(:,:,i)=imread('Y:\Public\mostzhangyalun\sulei\thy1\59_CROP_RESIZE\used.tif',i);

    tmpImage(:,:,(i-zRange(1)+1))=imread([src pre num2str(i,'%04d') suf]);
   
end

Image=tmpImage.*Ratio;



swc=load('Y:\Public\mostgroup\data_us\MBA-GF13004_cut\neutron\repair\test.txt');
swc(:,3:4)=swc(:,3:4)*10/3;
line=readLine(swc);

lineNum=size(line,1);


ball=sphericalArea(R);

thresh=minDistance(line);




for i=1:lineNum
    lineI=line{i};
    if(size(lineI,1)~=0)
        lineI=lineI(:,3:5);
        
        lightArea=chooseArea(lineI,R,ball);
        disp(i);
        for j=1:size(lightArea)
            x=lightArea(j,1);
            y=lightArea(j,2);
            z=lightArea(j,3);
            [x,y,z]=checkXYZ(x,y,z,width,height,level);
            Image(y,x,z)=tmpImage(y,x,z);
%             Image(y,x,z)=255;
        end
        
    end
end

Image=uint8(Image);

for i=1:level
    i
    imwrite(Image(:,:,i),[dst num2str(i,'%05d') '.tif']);
end

toc;
    

% pX=zeros(size(swc,1),1);
% pY=zeros(size(swc,1),1);
% pZ=zeros(size(swc,1),1);
% pR=zeros(size(swc,1),1);
% 
% pX=swc(:,3);
% pY=swc(:,4);
% pZ=swc(:,5);
% pR=swc(:,6);



% Elapsed time is 1016.081031 seconds.



