for i=1:newLevel
    
    imwrite(Image(:,:,i),[dst num2str(i,'%05d') '.tif']);
end