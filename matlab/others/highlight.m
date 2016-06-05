clc;


clear all;


% srcFile='Y:\Public\mostzhangyalun\sulei\thy1\3468-4267';
dstFile='Y:\Public\mostzhangyalun\sulei\matlab\test_dst\highlightTest\3';
nodeImfo=load('Y:\Public\mostzhangyalun\sulei\matlab\test\highlightTest\11-11_resize0.swc');;

% pre='test_';
% suf='_x3545_y_2092_w_1548_h_2235.tif';


zRange=[1,300];
width=1272;
height=1692;

decayRatio=0.1;
enhanceRatio=1;
neighbour=5;


level=zRange(2)-zRange(1)+1;
tic;
origImg = zeros(height,width,level);
toc;
%

% tic;


% 
% tic;
% for i = zRange(1):zRange(2) 
%     origImg(:,:,(i-zRange(1)+1)) = imread([srcFile '\' pre num2str(i,'%05d') suf]);
% end
% toc;

tic;
tmpImg=zeros(width,height,level);
for i = 1 : level
    
    tmpImg(:,:,i) = origImg(:,:,i)';
end
toc;

tmpImg=double(tmpImg);


tic;
origImg = tmpImg.*0;


toc;




[m,n]=size(nodeImfo);

tic;

for i=1:m
     x(i)=nodeImfo(i,3);
     y(i)=nodeImfo(i,4);
     z(i)=nodeImfo(i,5);
     r(i)=nodeImfo(i,6);
     r(i)=round(r(i));
     x(i)=x(i)*10/3;
     x(i)=round(x(i));
     y(i)=y(i)*10/3;
     y(i)=round(y(i));
     z(i)=round(z(i));
     
     
     if(x(i)>width)
         x(i)=width;
     end
     
     if(x(i)<1)
         x(i)=1;
     end

     if(y(i)>height)
         y(i)=height;
     end
     if(y(i)<1)
         y(i)=1;
     end
     

     if(z(i)>level)
         z(i)=level;
     end
     if(z(i)<1)
         z(i)=1;
     end


     xMax=x(i)+r(i)+neighbour;
     xMin=x(i)-r(i)-neighbour;
     if(xMax>width)
         xMax=width;
     end
     if(xMin<1)
         xMin=1;
     end
     yMax=y(i)+r(i)+neighbour;
     yMin=y(i)-r(i)-neighbour;
     if(yMax>height)
         yMax=height;
     end
     if(yMin<1)
         yMin=1;
     end
     zMax=z(i)+r(i)+neighbour;
     zMin=z(i)-r(i)-neighbour;
     if(zMax>level)
         zMax=level;
     end
     if(zMin<1)
         zMin=1;
     end

     for u=xMin:xMax
         for v=yMin:yMax
             for w=zMin:zMax
                 origImg(u,v,w)=255;
%                  origImg(u,v,w)=tmpImg(u,v,w)*enhanceRatio;
             end
         end
     end

end


tempImg2 = zeros(height,width,level);

for i = 1 : level
    
    tempImg2(:,:,i) = origImg(:,:,i)';
end

origImg=tempImg2;
origImg=uint8(origImg);

for i=1:level
    imwrite(origImg(:,:,i),[dstFile '\' num2str(i,'%05d') '.tif']);
end




toc;















% for i=1:width
%     for j=1:height
%         for k=1:zRange
% 
% 
%         %                  disp('here');
%          if(i/2==0)
%              origImg(i,j,k)=tmpImg(i,j,k)*0.1;
%          end
%         %                  flag=0;
%         %                  for h=1:num
%         %                      if([i,j,k]==notDoCoor{num})
%         %                          flag=1;
%         %                          break
%         %                      end
%         %                  end
%         %                  if(~flag)
% 
%         %                  end
%         %                  end
%         end
%     end
% end
 
% Elapsed time is 117.097016 seconds.
% Elapsed time is 3.009928 seconds.
% Elapsed time is 101.461689 seconds.
 
