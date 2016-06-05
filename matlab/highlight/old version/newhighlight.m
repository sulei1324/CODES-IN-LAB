% function newhighlight()
clear all;
clc;

width=464;
height=670;
zRange=[10000,10799];
level=zRange(2)-zRange(1)+1;

src=('Y:\Public\mostzhangyalun\sulei\thy1\59_CROP_RESIZE\resize\');
dst=('Y:\Public\mostzhangyalun\sulei\matlab\test_dst\highlightTest\9\');
pre='3468-4267-';
suf='.tif';

swc=load('W:\lsu\TDI072\figure\3\all_cell\swc\3_branch5.swc');
% swc(:,3:4)=swc(:,3:4)*10/3;
line=readLine(swc);
lineNum=size(line,1);

% ball=sphericalArea(R);
% 
% 
% Image=zeros(height,width,level);
% tmpImage=zeros(height,width,level);
% 
% 
% 
% tic;
% for i=zRange(1):zRange(2)
% %     tmpImage(:,:,i)=imread('Y:\Public\mostzhangyalun\sulei\thy1\59_CROP_RESIZE\used.tif',i);
%     
%     tmpImage(:,:,(i-zRange(1)+1))=imread([src pre num2str(i,'%05d') suf]);
%     
% end
% toc;
% 
% for i=1:lineNum
%     lineI=line{i};
%     if(size(lineI,1)~=0)
%         lineI=lineI(:,3:6);
%         lightArea=chooseArea(lineI);
%         disp(i);
%         for j=1:size(lightArea)
%             x=lightArea(j,1);
%             y=lightArea(j,2);
%             z=lightArea(j,3);
%             [x,y,z]=checkXYZ(x,y,z,width,height,level);
%             Image(y,x,z)=tmpImage(y,x,z);
% %             Image(y,x,z)=255;
%         end
%         
%     end
% end
% 
% Image=uint8(Image);
% 
% for i=1:level
%     i
%     imwrite(Image(:,:,i),[dst num2str(i,'%05d') '.tif']);
% end

toc;