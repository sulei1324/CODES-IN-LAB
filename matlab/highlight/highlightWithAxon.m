% function newhighlight()


clear all;
clc;
tic;
width=5072;
height=7000;
zRange=[768,1867];
imageImf=[width;height;zRange(1);zRange(2)];
level=zRange(2)-zRange(1)+1;

src=('Y:\Public\mostgroup\data_us\MBA-GF13004_cut\LDA\12-16\12_16-files\crop1_sub\');
dst=('Y:\Public\mostgroup\data_us\MBA-GF13004_cut\LDA\12-16\12_16-files\1\');
pre='crop1';
suf='.tif';
R=8;

swc1=load('Y:\Public\mostgroup\data_us\MBA-GF13004_cut\LDA\12-16\12_16-files\SpatialGraph1.swc');
swc1(:,3:4)=swc1(:,3:4)*10/3;
line1=readLine(swc1);
lineNum1=size(line1,1);
blockMax1=[];
blockMin1=[];
[blockMax1,blockMin1]=showMaxLocation(swc1,R,imageImf);

swc2=load('Y:\Public\mostgroup\data_us\MBA-GF13004_cut\LDA\12-16\12_16-files\SpatialGraph1_axon.swc');
swc2(:,3:4)=swc2(:,3:4)*10/3;
line2=readLine(swc2);
lineNum2=size(line2,1);
blockMax2=[];
blockMin2=[];
[blockMax2,blockMin2]=showMaxLocation(swc2,R,imageImf);

[totalMax,totalMin]=totalMaxMin(blockMax1,blockMax2,blockMin1,blockMin2);




% ball=sphericalArea(R);


newZrange=[totalMin(1,3)-totalMin(1,3),totalMax(1,3)-totalMin(1,3)];
newLevel=newZrange(2)-newZrange(1)+1;
newWidth=totalMax(1,1)-totalMin(1,1)+1;
newHeight=totalMax(1,2)-totalMin(1,2)+1;



Image=zeros(newHeight,newWidth,newLevel);
tmpImage=zeros(newHeight,newWidth,newLevel);
tmp=zeros(newHeight,newWidth);





% Range=[newZrange(1)-zRange(1)+1,newZrange(2)-zRange(1)+1];
% 
% Range=Range-1;

for i=newZrange(1):newZrange(2)
%     tmpImage(:,:,i)=imread('Y:\Public\mostzhangyalun\sulei\thy1\59_CROP_RESIZE\used.tif',i);
    disp(i);
    tic;
    tmp=imread([src pre num2str(i,'%05d') suf]);
    tmpImage(:,:,(i-newZrange(1)+1))=tmp(:,:);
    
    toc;
end


for i=1:lineNum1
    lineI1=line1{i};
    if(size(lineI1,1)~=0)
        lineI1=lineI1(:,3:6);
        lightArea1=chooseArea(lineI1,R);
        disp(i);
        for j=1:size(lightArea1)
            x=lightArea1(j,1);
            y=lightArea1(j,2);
            z=lightArea1(j,3);
            %Location Swift!!!!!!!!
            x=x-totalMin(1,1);
            y=y-totalMin(1,2);
            z=z-totalMin(1,3);
            [x,y,z]=checkXYZ(x,y,z,newWidth,newHeight,newLevel);
            Image(y,x,z)=tmpImage(y,x,z);
%              Image(y,x,z)=255;
        end
        
    end
end
for i=1:lineNum2
    lineI2=line2{i};
    if(size(lineI2,1)~=0)
        lineI2=lineI2(:,3:6);
        lightArea2=chooseArea(lineI2,R);
        disp(i);
        for j=1:size(lightArea2)
            x=lightArea2(j,1);
            y=lightArea2(j,2);
            z=lightArea2(j,3);
            %Location Swift!!!!!!!!
            x=x-totalMin(1,1);
            y=y-totalMin(1,2);
            z=z-totalMin(1,3);
            [x,y,z]=checkXYZ(x,y,z,newWidth,newHeight,newLevel);
            Image(y,x,z)=tmpImage(y,x,z);
%              Image(y,x,z)=255;
        end
        
    end
end






Image=uint8(Image);

for i=1:newLevel
    
    imwrite(Image(:,:,i),[dst num2str(i,'%05d') '.tif']);
end

toc;