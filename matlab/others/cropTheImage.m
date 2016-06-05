clc;
clear all;

inImage=imread('W:\lsu\movie\book\materials\3.bmp');
[height,width]=size(inImage);

wIn=width/10;
hIn=height/10;

for i=1:10
    for j=1:10
%         hIn*(j-1)+1
%         hIn*j
%         wIn*(i-1)+1
%         wIn*(i-1)+1:wIn*i
        tmpImage=inImage(hIn*(i-1)+1:hIn*i,wIn*(j-1)+1:wIn*j);
        tmpImage=uint8(tmpImage);
        imwrite(tmpImage,['W:\lsu\movie\book\materials\3\' num2str(i,'%02d') num2str(j,'%02d') '.bmp']);

    end
end
