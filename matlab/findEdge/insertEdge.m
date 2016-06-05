% 二值化时原尖锐地方会造成不连续


function insertEdge()

fileName='H:\sulei\轮廓制作\'
startName='H:\sulei\轮廓制作\test_05501_montage_edge.tif';
endName='H:\sulei\轮廓制作\test_05587_montage_edge.tif';

startImage=imread(startName);
endImage=imread(endName);

startImage=im2bw(startImage);
endImage=im2bw(endImage);

edge_s=findEdge(startImage,m,n);
edge_e=findEdge(endImage,m,n);

pre='test_';
suf='_montage_edge.tif';

l_fName=size(fileName);
l_p=size(startName);
startNum=startName(l_fName+l_p+1:l_fName+l_p+5);
endNum=endName(l_fName+l_p+1:l_fName+l_p+5);
startNum=str2num(startNum);
endNum=str2num(endName);
insertNum=endNum-startNum;


[m,n]=size(startImage);

gra_x1=0;
gra_y1=0;

gra_x2=0;
gra_y2=0;

num1=0;
num2=0;

for i=1:m
    for j=1:n
        if(startImage(i,j)==1)  
            gra_x1=gra_x1+i;
            gra_y1=gra_y1+j;
            num1=num1+1;
        end
    end
end

gra_x1=round(gra_x1/num);
gra_y1=round(gra_y1/num);

for i=1:m
    for j=1:n
        if(endImage(i,j)==1)  
            gra_x2=gra_x2+i;
            gra_y2=gra_y2+j;
            num2=num2+1;
        end
    end
end

gra_x2=round(gra_x2/num2);
gra_y2=round(gra_y2/num2);


for k=1:insertNum
    ratio_s=(insertNum+1-k)/(insertNum+1);
    ratio_e=(k)/(insertNum+1);
    gra_xt=ratio_s*gra_x1+ratio_e*gra_x2;
    gra_yt=ratio_s*gra_y1+ratio_e*gra_y2;
    for i=1:m
        for j=1:n
        




        
        