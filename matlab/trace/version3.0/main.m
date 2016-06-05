clc;
clear all;
tic;
swc=load('W:\lsu\movie\book\trace\I5\I5.swc');
src='Y:\Public\mostPreprocess\MBA-GF13004_compress\correct\';
dst='W:\lsu\matlab\test_dst\trace\2\';
width=23400;
height=32200;
outWidth=1000;
outHeight=618;
zRange=[101,6100];
pre='test_';
suf='_correct.tif';
interval=30;
% overlap=400;
R=8;
inImage=zeros(height,width);
% outImage=zeros(height,width);
% f=dir(src);
% pRange=projectRange(src);
% swc(:,3:4)=swc(:,3:4)*10/3;
lineArray=readLine(swc);
lineNum=size(lineArray,1);
lineLong=zeros(lineNum,2);
for i=1:lineNum
    lineLong(i,1)=size(lineArray{i,1},1);
    lineLong(i,2)=i;
end
m=max(lineLong(:,1));
l=find(lineLong(:,1)==m);
n=size(l,1);

for j=1:n
    whichLine=lineLong(l(1,j),2);
    maxLineNum=lineLong(l(1,j),1);
    singleLineSwc=zeros(maxLineNum,7);
    xyz=zeros(1,3);
    for i=1:maxLineNum
        singleLineSwc(i,1)=i;
        singleLineSwc(i,2)=1;
        singleLineSwc(i,3:5)=round(lineArray{whichLine,1}(i,3:5));
        singleLineSwc(i,6)=1;
        if(i==1)
            singleLineSwc(i,7)=-1;
        else
            singleLineSwc(i,7)=i-1;
        end
    end
end

dlmwrite('W:\lsu\movie\book\trace\I5\max.swc',singleLineSwc,'delimiter',' ',  'newline','pc');


% format long;
% maxZ=max(singleLineSwc(:,5));
% minZ=min(singleLineSwc(:,5));
% 
% zNum=maxZ-minZ+1;
% zCollect={};
% 
% for i=1:zNum
%     z=i+minZ-1;
%     sameZindex=find(singleLineSwc(:,5)==z);
%     zCollect{i,1}=singleLineSwc(sameZindex,3:5);
% end
% 
% zCollectX={};
% index=0;
% for i=1:interval:zNum
%     index=index+1;
%     zS=i;
%     tmp=[];
%     if(i+interval>=zNum)
%         zE=zNum;
%     else
%         zE=i+interval;
%     end
%     for j=zS:zE
%         tmp=[tmp;zCollect{j,1}];
%     end
%     zCollectX{index,1}=tmp;
% end
% 
% zCollectXnum=size(zCollectX,1);
% areaZx=zeros(index,4);
% for i=1:index
%     xyz=zCollectX{i,1};
%     maxX1=max(xyz(:,1));
%     minX1=min(xyz(:,1));
%     maxY1=max(xyz(:,2));
%     minY1=min(xyz(:,2));
%     areaZx(i,1:4)=[minX1,maxX1,minY1,maxY1];
% end
% 
% maxXrange=max(areaZx(:,2)-areaZx(:,1))+1;
% maxYrange=max(areaZx(:,4)-areaZx(:,3))+1;
%     
% everySx=round((areaZx(:,2)-areaZx(:,1))/2)+areaZx(:,1)-round(outWidth/2)+1;
% everyEx=round((areaZx(:,2)-areaZx(:,1))/2)+areaZx(:,1)+round(outWidth/2);
% everySy=round((areaZx(:,4)-areaZx(:,3))/2)+areaZx(:,3)-round(outHeight/2)+1;    
% everyEy=round((areaZx(:,4)-areaZx(:,3))/2)+areaZx(:,3)+round(outHeight/2);        
% 
% 
% 
% % outImage=zeros(outHeight,outWidth,3);
% % for i=1:zCollectXnum
% %     outImage=zeros(outHeight,outWidth,3);
% %     xyz=zCollectX{i,1};
% %     l=size(xyz,1);
% %     for j=1:l
% %         x=xyz(j,1)-everySx(i,1)+1;
% %         y=xyz(j,2)-everySy(i,1)+1;
% %         outImage(y,x,:)=[1,0,0];
% %     end
% %     imshow(outImage);
% % end
% 
% for i=1:zCollectXnum
%     tmpImage=zeros(outHeight,outWidth);
%     outImage=zeros(outHeight,outWidth);
%     tmpImage=uint8(tmpImage);
%     outImage=uint8(outImage);
%     disp('start');
%     xyz=zCollectX{i,1};
%     l=size(xyz,1);
%     minZ3=min(xyz(:,3));
%     maxZ3=max(xyz(:,3));
%     for k=minZ3:maxZ3
%         zSerial=k+100;
%         zSerialStr=num2str(zSerial,'%05d');
%         inImage=imread([src pre zSerialStr suf]);
%         disp(['reading ' src pre zSerialStr suf]);
%         tmpImage=inImage(everySy(i,1):everyEy(i,1),everySx(i,1):everyEx(i,1));
%         outImage=max(outImage,tmpImage);
%     end
%    
%     imwrite(outImage,[dst pre num2str(i,'%05d') '_raw' suf])
% 
% end



% % % for i=1:zCollectXnum
% % %     xyz=zCollectX{i,1};
% % %     l=size(xyz,1);
% % %     minZ3=min(xyz(:,3));
% % %     maxZ3=max(xyz(:,3));
% % %     rgbImage=zeros(outHeight,outWidth,3)
% % %     for j=1:l
% % %         x=xyz(j,1)-everySx(i,1)+1;
% % %         y=xyz(j,2)-everySy(i,1)+1;
% % %         rgbImage(y,x,:)=[1,0,0];
% % %     end
% % % 
% % %     imwrite(rgbImage,[dst pre num2str(i,'%05d') suf]);
% % %     disp(['writen ' num2str(i,'%05d')]);
% % % 
% % % end
% % 
% % % stackStart=[1:interval:zNum];
% % % 
% % % stackNum=size(stackStart,2);
% % % stackEnd=zeros(1,stackNum);
% % % 
% % % for i=1:stackNum
% % %     if((stackStart(i)+overlap)>zNum)
% % %         stackEnd(i)=zNum;
% % %     else
% % %         stackEnd(i)=stackStart(i)+overlap-1;
% % %     end
% % %     
% % % end
% % % 
% % % 
% % % singleLineSwc(:,3:5)=round(singleLineSwc(:,3:5));
% % % 
% % % outXYZ=sortByZ(singleLineSwc(:,3:5));
% % % flag=0;
% % % slice={};
% % % outImageArray={};
% % % eachImageRangeInRaw=[];
% % % for i=1:stackNum
% % %     zStart=stackStart(1,i);
% % %     zEnd=stackEnd(1,i);
% % %     if(zEnd==zNum)
% % %         flag=1;
% % %     end
% % %     disp(stackNum);
% % %     index=1;
% % %     slice={};
% % % 
% % %     
% % %     for j=zStart:zEnd
% % %         disp(j);       
% % %         slice{index,1}=outXYZ{j,1};
% % %         index=index+1;
% % %         
% % %     end
% % %     [w,h,x,y]=chooseLocation(slice,width,height);
% % %     [x,y]=checkXY(x,y,width,height);  
% % %     eachImageRangeInRaw=[eachImageRangeInRaw;x;y];
% % %     zStart=zStart+minZ+zRange(1,1)-2;
% % %     zEnd=zEnd+minZ+zRange(1,1)-2;
% % %     whichProImage=chooseProjectImage(zStart,zEnd,pRange);
% % %     whichProImage=whichProImage+2;
% % %     
% % %     outImage0=zeros(h,w);
% % %     tmp=zeros(h,w);
% % %     proImageNum=size(whichProImage,1);
% % %     for j=1:proImageNum        
% % %         tic;
% % %         disp(['read from: ' src f(whichProImage(j)).name]);
% % %         inImage=imread([src f(whichProImage(j)).name]);        
% % %         tmp=inImage(y(1,1):y(1,2),x(1,1):x(1,2));
% % %         tmp=double(tmp);
% % %         outImage0=max(tmp,outImage0); 
% % %         toc;
% % %     end    
% % %     tic;
% % %     disp(['collect image']);
% % %     outImageArray{i,1}=outImage0;
% % %     toc;
% % %     if(flag==1)
% % %         break;
% % %     end
% % %     
% % %     %     outRgbImage=zeros(h,w,3);
% % %     %     outRgbImage=rgbImage(y(1,1):y(1,2),x(1,1):x(1,2),1:3);
% % %     %     disp(['write to:  ' dst pre num2str(i,'%02d') '.jpg']);
% % %     %     imwrite(outImage,[dst pre num2str(i,'%02d') '.jpg']);  
% % % end
% % % 
% % % imageNum=size(outImageArray,1);
% % % % for i=imageNum:-1:1
% % % for i=1:imageNum
% % %     tmpImage=zeros(height,width);
% % %     xStart=eachImageRangeInRaw(2*i-1,1);
% % %     xEnd=eachImageRangeInRaw(2*i-1,2);
% % %     yStart=eachImageRangeInRaw(2*i,1);
% % %     yEnd=eachImageRangeInRaw(2*i,2);
% % % %     outImage(yStart:yEnd,xStart:xEnd)=outImageArray{i,1}(:,:);
% % %     tmpImage(yStart:yEnd,xStart:xEnd)=outImageArray{i,1}(:,:);
% % %     outImage=max(outImage,tmpImage);
% % % end
% % % 
% % % 
% % % 
% % % 
% % % outImage=uint8(outImage);
% % % 
% % % disp(['write to:  ' dst pre 'trace' suf]);
% % % imwrite(outImage,[dst pre 'trace' suf]);
% % toc;
% % 
% % % tic;
% % % rgbImage=creatRGB(singleLineSwc,R,width,height);
% % % toc;
% % % imshow(rgbImage);
% % % disp(['write to:  ' dst pre 'trace_rgb' '.jpg']);
% % % imwrite(rgbImage,[dst pre 'trace_rgb' '.jpg']);
% %         
% % 
% % %     for j=zStart:zEnd
% % % 
% % %         
% % % %         
% % %         tic;
% % % %         inImage=imread('./0.tif');   
% % %         inImage=imread([src pre num2str(imageNum,'%05d') suf]);
% % %         disp([src pre num2str(imageNum,'%05d') suf]);
% % %         tmp=inImage(y(1,1):y(1,2),x(1,1):x(1,2));
% % %         outImage=max(tmp,outImage);        
% % %         toc;
% % %     end
% % 
% % % dlmwrite('.\maxLine.swc',singleLineSwc,'delimiter',' ','newline','pc');
    