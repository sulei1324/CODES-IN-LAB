% % clc;
% % clear all;
% % 
% % swc=load('I9.swc');
% % src='Y:\Archive\MBA-GF13004_preprocess\Src_Pro\allproject\';
% % dst='Y:\Public\mostzhangyalun\sulei\matlab\test_dst\trace\';
% % width=23400;
% % height=32200;
% % zRange=[101,6100];
% % pre='test_';
% % suf='.tif';
% % interval=300;
% % overlap=400;
% % R=8;
% % inImage=zeros(height,width);
% % f=dir(src);
% % pRange=projectRange(src);
% % swc(:,3:4)=swc(:,3:4)*10/3;
% % lineArray=readLine(swc);
% % lineNum=size(lineArray,1);
% % lineLong=zeros(lineNum,2);
% % for i=1:lineNum
% %     lineLong(i,1)=size(lineArray{i,1},1);
% %     lineLong(i,2)=i;
% % end
% % m=max(lineLong(:,1));
% % l=find(lineLong(:,1)==m);
% % n=size(l,1);
% % 
% % for j=1:n
% %     whichLine=lineLong(l(1,j),2);
% %     maxLineNum=lineLong(l(1,j),1);
% %     singleLineSwc=zeros(maxLineNum,7);
% %     xyz=zeros(1,3);
% %     for i=1:maxLineNum
% %         singleLineSwc(i,1)=i;
% %         singleLineSwc(i,2)=1;
% %         singleLineSwc(i,3:5)=round(lineArray{whichLine,1}(i,3:5));
% %         singleLineSwc(i,6)=1;
% %         if(i==1)
% %             singleLineSwc(i,7)=-1;
% %         else
% %             singleLineSwc(i,7)=i-1;
% %         end
% %     end
% % end
% % tic;
% % rgbImage=creatRGB(singleLineSwc,R,width,height);
% % toc;
% 
% 
% format long;
% maxZ=max(singleLineSwc(:,5));
% minZ=min(singleLineSwc(:,5));
% 
% zNum=maxZ-minZ+1;
% 
% stackStart=[1:interval:zNum];
% 
% stackNum=size(stackStart,2);
% stackEnd=zeros(1,stackNum);
% 
% for i=1:stackNum
%     if((stackStart(i)+overlap)>zNum)
%         stackEnd(i)=zNum;
%     else
%         stackEnd(i)=stackStart(i)+overlap-1;
%     end
%     
% end
% 
% 
% singleLineSwc(:,3:5)=round(singleLineSwc(:,3:5));
% 
% outXYZ=sortByZ(singleLineSwc(:,3:5));
% flag=0;
% slice={};
% 
% 
% for i=1:stackNum
%     zStart=stackStart(1,i);
%     zEnd=stackEnd(1,i);
%     if(zEnd==zNum)
%         flag=1;
%     end
%     disp(stackNum);
%     index=1;
%     slice={};
%     
%     
%     for j=zStart:zEnd
%         disp(j);       
%         slice{index,1}=outXYZ{j,1};
%         index=index+1;
%         
%     end
%     [w,h,x,y]=chooseLocation(slice,width,height);
%     [x,y]=checkXY(x,y,width,height);
% %     zStart=zStart+minZ+zRange(1,1)-2;
% %     zEnd=zEnd+minZ+zRange(1,1)-2;
% %     whichProImage=chooseProjectImage(zStart,zEnd,pRange);
% %     whichProImage=whichProImage+2;
%     outRgbImage=zeros(h,w,3);
%     outRgbImage=rgbImage(y(1,1):y(1,2),x(1,1):x(1,2),1:3);
%     
% %     proImageNum=size(whichProImage,1);
% %     for j=1:proImageNum        
% %         tic;
% %         disp(['read from: ' src f(whichProImage(j)).name]);
% %         inImage=imread([src f(whichProImage(j)).name]);
% %         
% %         tmp=inImage(y(1,1):y(1,2),x(1,1):x(1,2));
% %         tmp=double(tmp);
% %         outImage=max(tmp,outImage); 
% %         toc;
% %     end
%     
%     
%     
% 
%     
%     tic;
%     disp(['write to:  ' dst pre num2str(i,'%02d') '.jpg']);
%     imwrite(outImage,[dst pre num2str(i,'%02d') '.jpg']);
%     toc;
%     if(flag==1)
%         break;
%     end
% end


clc;

for i=435:30:7214
    
    disp(i);
end
