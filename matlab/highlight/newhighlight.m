% function newhighlight()


clear all;
clc;
tic;
width=3025;
height=2423;
zRange=[0,565];
imageImf=[width;height;zRange(1);zRange(2)];
level=zRange(2)-zRange(1)+1;

src=('Y:\Public\mostgroup\data_us\MBA-GF13004_cut\LDA\12-16\12_16-files\crop1_sub\');
dst=('Y:\Public\mostgroup\data_us\MBA-GF13004_cut\LDA\12-16\12_16-files\1\');
pre='crop1';
suf='.tif';
R=8;

swc=load('Y:\Public\mostgroup\data_us\MBA-GF13004_cut\LDA\12-16\12_16-files\SpatialGraph1.swc');
swc(:,3:4)=swc(:,3:4)*10/3;
line=readLine(swc);
lineNum=size(line,1);


blockMax=[];
blockMin=[];
[blockMax,blockMin]=showMaxLocation(swc,R,imageImf);

% ball=sphericalArea(R);


% newZrange=[blockMin(1,3)-blockMin(1,3),blockMax(1,3)-blockMin(1,3)];
% newLevel=newZrange(2)-newZrange(1)+1;
% newWidth=blockMax(1,1)-blockMin(1,1)+1;
% newHeight=blockMax(1,2)-blockMin(1,2)+1;



Image=zeros(height,width,level);
tmpImage=zeros(height,width,level);
tmp=zeros(height,width);





% Range=[newZrange(1)-zRange(1)+1,newZrange(2)-zRange(1)+1];
% 
% Range=Range-1;

for i=zRange(1):zRange(2)
%     tmpImage(:,:,i)=imread('Y:\Public\mostzhangyalun\sulei\thy1\59_CROP_RESIZE\used.tif',i);
    disp(i);
    tic;
    tmp=imread([src pre num2str(i,'%05d') suf]);
    tmpImage(:,:,(i-zRange(1)+1))=tmp(:,:);
    
    toc;
end


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
            %Location Swift!!!!!!!!
            x=x-blockMin(1,1);
            y=y-blockMin(1,2);
            z=z-blockMin(1,3);
            [x,y,z]=checkXYZ(x,y,z,width,height,level);
            Image(y,x,z)=tmpImage(y,x,z);
%              Image(y,x,z)=255;
        end
        
    end
end

Image=uint8(Image);

for i=1:level
    
    imwrite(Image(:,:,i),[dst num2str(i,'%05d') '.tif']);
end

toc;