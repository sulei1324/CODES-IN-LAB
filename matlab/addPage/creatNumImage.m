function outImage=creatNumImage(pageNum,boldSize)


fontStr=num2str(pageNum);
sLen=size(fontStr,2);
fontNum=creatNum();

outImageSingle=zeros(boldSize*5,boldSize*3);
[m,n]=size(outImageSingle);
outImage=zeros(m,n+boldSize*sLen);


for i=1:sLen
    outImageSingle=zeros(boldSize*5,boldSize*3);
    numStr=fontStr(i);
    num=str2num(numStr);
    if(num==0)
        fontRaw=fontNum{10,1};
    else
        fontRaw=fontNum{num,1};
    end
    for j=1:5
        for k=1:3
            if(fontRaw(j,k)==1)
                outImageSingle(boldSize*(j-1)+1:boldSize*j,boldSize*(k-1)+1:boldSize*(k))=255;
            end
        end
    end
    outImageSingle=uint8(outImageSingle);
    imshow(outImageSingle);
    outImage(:,(i-1)*boldSize*4+1:(i-1)*boldSize*4+boldSize*3)=outImageSingle(:,:);
end

outImage=uint8(outImage);
imshow(outImage);
