clc;
clear all;

A = imread('./1/2.tif');
B = fftshift(fft2(A));

C = abs(B);
subplot(4, 1, 1);
imshow(A, []);
D = log(C);
subplot(4, 1, 2);
imshow(D, []);


[N1, N2] = size(D);
n = 2;
d0 = 5;
n1 = fix(N1 / 2);
n2 = fix(N2 / 2);
for i = 1 : N1
    for j = 1 : N2
        d = sqrt((i - n1) ^ 2 + (j - n2) ^ 2);
        if d >= 20 && d <= 30
            h = 0;
        else if d >=40 && d <=80
                h = 0;
%             h = 1 / (1 + (d / d0) ^ (2 * n));
            else
                
            h = 1;
            end
        end
        result(i, j) = h * B(i, j);
    end
end

F3 = log(abs(result));
subplot(4, 1, 3);
imshow(F3, []);
result = ifftshift(result);
X2 = ifft2(result);
X3 = uint8(real(X2));
subplot(4, 1, 4);
imshow(X3);
imwrite(X3, './1/1.tif');
