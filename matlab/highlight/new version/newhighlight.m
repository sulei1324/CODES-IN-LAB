% function newhighlight()


clear all;
clc;
tic;
width=1548;
height=2235;
zRange=[3468,4267];
level=zRange(2)-zRange(1)+1;

src=('Y:\Public\mostgroup\data_us\MBA-GF13004_cut\neuron\repair\3-7\3-7_sub\');
dst=('Y:\Public\mostgroup\data_us\MBA-GF13004_cut\neuron_chosen\3-7-1\image\');
pre='temp';
suf='.tif';
R=8;
swc=load('Y:\Public\mostgroup\data_us\MBA-GF13004_cut\neuron_chosen\3-7-1\test.swc');

swc(:,3:4)=swc(:,3:4)*10/3;
line=readLine(swc);
lineNum=size(line,1);

% ball=sphericalArea(R);


Image=zeros(height,width,level);
tmpImage=zeros(height,width,level);




for i=zRange(1):zRange(2)
%     tmpImage(:,:,i)=imread('E:\sulei\hippo-sub.tif',i);
    
     tmpImage(:,:,(i-zRange(1)+1))=imread([src pre num2str(i,'%05d') suf]);
    
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