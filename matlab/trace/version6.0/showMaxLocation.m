function [maxL,minL]=showMaxLocation(swc,R,imageImf)

line=readLine(swc);
lineNum=size(line,1);
maxX=0;
maxY=0;
maxZ=0;
minX=imageImf(1,1);
minY=imageImf(2,1);
minZ=imageImf(4,1)-imageImf(3,1)+1;
maxL=[0,0,0];
minL=[minX,minY,minZ];
width=imageImf(1,1);
height=imageImf(2,1);
level=imageImf(4,1)-imageImf(3,1)+1;




for i=1:lineNum
    lineI=line{i};
    if(size(lineI,1)~=0)
        lineI=lineI(:,3:6);
        lightArea=chooseArea(lineI,R);
        disp(i);
        for j=1:size(lightArea)
            x=lightArea(j,1);
            y=lightArea(j,2);
            z=lightArea(j,3);
            [x,y,z]=checkXYZ(x,y,z,width,height,level);
            [maxL,minL]=findMaxMin(x,y,z,maxL,minL);
        end
    

            

   end
        
end

end


%             Image(y,x,z)=tmpImage(y,x,z);
%             Image(y,x,z)=255;
% width=23400;
% height=32200;
% level=7334;
% zRange=[50000,50599];
% level=zRange(2)-zRange(1)+1;
% src=('Y:\Public\mostgroup\data_us\MBA-GF13004_cut\neutron\repair\55\55_sub\');
% dst=('Y:\Public\mostgroup\data_us\MBA-GF13004_cut\neutron\repair\55\55_3\');
% pre='5';
% suf='.tif';
% ball=sphericalArea(R);
% Image=zeros(height,width,level);
% tmpImage=zeros(height,width,level);
% for i=zRange(1):zRange(2)
% %     tmpImage(:,:,i)=imread('Y:\Public\mostzhangyalun\sulei\thy1\59_CROP_RESIZE\used.tif',i);
%     
%     tmpImage(:,:,(i-zRange(1)+1))=imread([src pre num2str(i,'%05d') suf]);
%     
% end
% toc
% swc=load('Y:\Public\mostgroup\data_us\MBA-GF13004_cut\LDA\trace-16-22\SpatialGraph1.swc');
% swc(:,3:4)=swc(:,3:4)*10/3;

