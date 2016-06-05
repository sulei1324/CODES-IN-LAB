function [mD]=meanDistance(line)

% clear all;
% clc;
wholeD=0;
pointNum=size(line,1);

for i=2:pointNum
    d=distanceXYZ(line(i-1,1:3),line(i,1:3));
    wholeD=wholeD+d;
end
mD=wholeD/(pointNum-1);    






% lineNum=size(line,1);
% 
% for i=1:lineNum
%     lineXYZ=line{i}(:,3:5);
%     lLine=size(lineXYZ,1);
%     wholeD=0;
%     for j=2:lLine
%         d=distanceXYZ(lineXYZ(j-1,1:3),lineXYZ(j,1:3));
%         wholeD=wholeD+d;
%     end
%     mD(i,1)=wholeD/(lLine-1);
% end
%         
% 
% 
% 
% 
% end


% Swc=load('Y:\Public\mostzhangyalun\sulei\matlab\m\highlight\1.txt');
% l=size(Swc,1);
% wholeD=0;
% for i=2:l
%         d=distanceXYZ(Swc(i-1,3:5),Swc(i,3:5));
%         wholeD=wholeD+d;
% end
% 
% mean=wholeD/(l-1)