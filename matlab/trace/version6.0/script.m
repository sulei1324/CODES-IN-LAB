    for j=1:dimNum
        xyzD=xyz2(:,:,j);
        pNum=size(xyzD,1);
        for o=pNum:-1:1
            if(xyzD(o,1)==0)
                xyzD(o,:)=[];
            end
        end
    end