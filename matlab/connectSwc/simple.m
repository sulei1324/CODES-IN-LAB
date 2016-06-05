clc;

clear all;

partNum=2;
src='W:\lsu\movie\book\trace\I9\';
pre='I9_part';
post='.swc';
dst='W:\lsu\movie\book\trace\I9\';
writePre='I9';
writePost='axonWithX3.swc';
swc=[];
lCur=0;
lPre=0;
for i=1:partNum
    tmp=load([src pre num2str(i) post]);
    lCur=size(tmp,1);
    if(i~=1)
        for j=1:lCur
            if (tmp(j,7)==-1)
                tmp(j,1)=tmp(j,1)+lPre;
                continue;
            else
                tmp(j,1)=tmp(j,1)+lPre;
                tmp(j,7)=tmp(j,7)+lPre;
            end
        end
    end
    swc=[swc;tmp];
    lPre=lPre+size(tmp,1);
end

dlmwrite([dst writePre writePost],swc,'delimiter',' ',  'newline','pc');