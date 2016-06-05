load  Y:\Public\mostgroup\data_us\MBA-GF13004_100-6100\I2_files\2\test_axon.swc
test=test_axon;
len=size(test,1);
test1=zeros(len,7);
for i =1:len
    test1(i,1)=test(i,1);
    test1(i,2)=test(i,2);
    test1(i,3)=test(i,3)-3900*0.3;
    test1(i,4)=test(i,4)-11500*0.3;
    test1(i,5)=test(i,5)-1487;
    test1(i,6)=test(i,6);
    test1(i,7)=test(i,7);
end
% test1=unit8(test1);
dlmwrite('Y:\Public\mostgroup\data_us\MBA-GF13004_100-6100\I2_files\2\I2_axon-new.swc',test1,'delimiter','\t','precision',6);
disp('done')