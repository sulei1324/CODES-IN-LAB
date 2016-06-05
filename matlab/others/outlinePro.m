% clc;
% clear all;
% 
% src='Y:\Public\mostgroup\data_us\MBA-GF13004_cut\13004-6z\temp\';
% outline='Y:\Public\mostgroup\data_us\MBA-GF13004_cut\13004-6z\13004-outline-6x6y6z\';
dst='Y:\Public\mostgroup\data_us\MBA-GF13004_cut\13004-6z\new\';
% width=1170;
% height=1610;
% num=[26:6:7334];
% l=size(num,2);
% srcImage=zeros(height,width,l);
% outlineImage=zeros(height,width,l);
% 
% 
% 
% for i=1:l
%     disp(i);
%     n=num(i);
%     tic;
%     srcImage(:,:,i)=imread([src 'test_' num2str(n,'%05d') '_re.tif']);
%     outlineImage(:,:,i)=imread([outline 'GF13004_' num2str(n,'%05d') '_re.tif']);
%     toc;
% end

% for z=1:l
%     tic;
%     for i=1:width
%         for j=1:height
%             if(outlineImage(j,i,z)==0)
%                 srcImage(j,i,z)=0;
%             end
%         end
%     end
%     toc;
% end


% srcImage=uint8(srcImage);
for z=1:l
    tic;
    disp(z);
    n=num(z);
    imwrite(srcImage(:,:,z),[dst 'outline_' num2str(n,'%05d') '.tif']);
    toc;
end

        

    