
clc;
clear all;

swc_axon = load('I:\a\TDI21301010-cell3\axons_3.swc');
swc_den = load('I:\a\TDI21301010-cell3\dendrites_3.swc');
swc_cell = load('I:\a\TDI21301010-cell3\soma_3.swc');
m1 = size(swc_cell,1);
m2 = size(swc_axon, 1);
m3 = size(swc_den, 1);
newSwc = zeros(m1 + m2 + m3,7);
for i = 1 : m1 + m2 + m3
    if i <= m1
        newSwc(i, :) = swc_cell(i, :);
        newSwc(i, 2) = 1;
    else if i > m1 && i <= m1 + m2
            newSwc(i, :) = swc_axon(i - m1, :);
            newSwc(i, 2) = 2;
            newSwc(i, 1) = newSwc(i, 1) + m1;
            if newSwc(i, 7) ~= -1
                newSwc(i, 7) = newSwc(i, 7) + m1;
            end
        else if i > m1 + m2
                newSwc(i, :) = swc_den(i - m1 - m2, :);
                newSwc(i, 2) = 3;
                newSwc(i, 1) = newSwc(i, 1) + m1 + m2;
                if newSwc(i, 7) ~= -1
                    newSwc(i, 7) = newSwc(i, 7) + m1 + m2;
                end
            end
        end
    end
    
            
end

newSwc(:, 6) = 0.4;

dlmwrite(['I:\a\TDI21301010-cell3\Cell3-merged.swc'],newSwc,'delimiter','\t','precision',6);
