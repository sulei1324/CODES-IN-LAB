clear all;
clc;
tic;
width=3840;
height=2344;
zRange=[1,700];
level=zRange(2)-zRange(1)+1;

src=('Y:\Public\mostgroup\data_us\MBA-GF13004_cut\neutron\repair\48\48_sub\');
dst=('Y:\Public\mostzhangyalun\sulei\matlab\test_dst\48\2\');
pre='48';
suf='.tif';
R=5;

swc=load('Y:\Public\mostgroup\data_us\MBA-GF13004_cut\neutron\repair\48\test.txt');
swc(:,3:4)=swc(:,3:4)*10/3;
line=readLine(swc);
lineNum=size(line,1);

% ball=sphericalArea(R);


Image=zeros(height,width,level);
tmpImage=zeros(height,width,level);




for i=zRange(1):zRange(2)
%     tmpImage(:,:,i)=imread('Y:\Public\mostzhangyalun\sulei\thy1\59_CROP_RESIZE\used.tif',i);
    
    tmpImage(:,:,(i-zRange(1)+1))=imread([src pre num2str(i,'%04d') suf]);
    
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