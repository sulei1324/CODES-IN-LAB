function [zCollectWithImageX]=makeX(zCollectWithImage)

wi=1;
while(wi<zInvolvedNum)
    if(wi==1)
        index=1;
    end
    involvedImNum=1;
    curProName=zCollectWithImage{wi,2};
    involedProName=curProName;
    xyzX=zCollectWithImage{wi,1};
    for j=wi+1:zInvolvedNum
       thisProName=zCollectWithImage{j,2};
       if(~strcmp(curProName,thisProName))
           curProName=thisProName;
           involvedImNum=involvedImNum+1;
           if(involvedImNum<=interval)
               involedProName=[involedProName;thisProName]; 
           end
           if(involvedImNum==(interval-overlap+1))
               wi=j;
           end
       end
       if(involvedImNum<=interval)          
           tmpXYZ30=zCollectWithImage{j,1};
           xyzX=[xyzX;tmpXYZ30];
        else
            break;
        end
    end
%     xyz30=unique(xyz30,'rows');
    xyzX=sortrows(xyzX);
    zCollectX{index,1}=xyzX;
    zCollectX{index,2}=involedProName;
    index=index+1;
    if(j==zInvolvedNum)
        break;
    end
end


end