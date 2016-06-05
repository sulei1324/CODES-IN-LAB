% dlmwrite('W:\lsu\anlysis\raw\I9_x1.txt',maxCoord,'delimiter',' ','newline','pc');
% dlmwrite('W:\lsu\anlysis\raw\I9_x1.txt',minCoord,'-append','delimiter',' ','newline','pc');

f=fopen('W:\lsu\anlysis\raw\I9_x1.txt','w+');

fwrite(f,80);
% frewind(f);
a=fread(f);


fclose(f);
