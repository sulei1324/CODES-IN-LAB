clc;
clear all;

A = imread('./1/2.tif');
B = fftshift(fft2(A));

% subplot(2, 3, 1);
% imshow(A);
% subplot(2, 3, 2);
C = abs(B);
imshow(C, []);
% % subplot(2, 3, 3);
D = log(C);
figure, imshow(D, []);
% subplot(2, 3, 4);
% imshow(angle(B), []);
% subplot(2, 3, 4);
% imshow(real(B), []);
% subplot(2, 3, 4);
% imshow(imag(B), []);

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
figure, imshow(F3, []);
result = ifftshift(result);
X2 = ifft2(result);
X3 = uint8(real(X2));
figure, imshow(X3);
imwrite(X3, './1/1.tif');
