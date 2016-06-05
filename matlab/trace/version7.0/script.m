% xyz207=zCollectX{207,1};
% l207=size(xyz207,1);
% for i=1:l207
%     hold on;
%     pause(1);
%     plot(zCollectX{207,1}(1:i,1),zCollectX{207,1}(1:i,2),'r*');
% end

xyz44=zCollectX1{45,1};
dim44=size(xyz44,3);
for i=1:dim44
    xyz44d=xyz44(:,:,i);
    lDim=size(xyz44d,1);
    for j=1:lDim
        if(i==1)
            hold on;
            if(xyz44d(j,3)==0)
                continue;
            else
                plot(xyz44d(j,4),xyz44d(j,3),'r*');
            end
            disp(i);
        else
            hold on;
            disp(i);
            if(xyz44d(j,3)==0)
                continue;
            else
                plot(xyz44d(j,4),xyz44d(j,3),'g.');
            end
        end
    end
end