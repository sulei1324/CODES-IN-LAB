function readFile()
f=load('test_01368_out_edge.txt');
[m,n]=size(f);
edge={};
num=0;

for i=1:n
    for j=1:m
        num=num+1;
        edge_x(num)=floor(f(j,i));
        temp=f(j,i)-floor(f(j,i));
        edge_y(num)=floor(10000*temp);
        edge{num}=[edge_x(num),edge_y(num)];
    end
end

edge_x=sort(edge_x);
edge_y=sort(edge_y);
x_min=edge_x(1);
x_max=edge_x(end);
y_min=edge_y(1);
y_max=edge_y(end);

outImage=ones(x_max+1,y_max+1);

for k=1:num
    if(edge{k}(2)==0)
        edge{k}(2)=1;
    end
    outImage(edge{k}(1),edge{k}(2))=0;
end

imwrite(outImage,'edge.tif');
