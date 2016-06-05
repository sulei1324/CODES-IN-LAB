function [zCollect] = assignImage(zCollect,src,pre,suf)

for i=1:zInvolvedNum
    xyz2=zCollect{i,1};
    dime2=size(xyz2,3);
    zSerial=xyz2(1,5,1);
    if((i==1)||(zSerial>=(startZserial+10)))
        readFlag=1;
    else
        readFlag=0;        
    end
    zSerialStr=num2str(zSerial,'%05d');
    if(readFlag)
        if(zSerial==floor(zSerial/10)*10)
            startZserial=(floor(zSerial/10)-1)*10+1;
        else
            startZserial=floor(zSerial/10)*10+1;
        end
        if(((startZserial>=351)&&(startZserial<=1991))||(startZserial==2241))
            endZserial=startZserial+9;
        else
            endZserial=startZserial+10;
        end        
    end 
    involvedPrImNa=[src pre num2str(startZserial,'%05d') '-' num2str(endZserial,'%05d')  suf];
    zCollect{i,2}=involvedPrImNa;
end

end

