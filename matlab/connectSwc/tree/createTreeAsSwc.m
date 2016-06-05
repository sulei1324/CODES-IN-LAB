function createTreeAsSwc(s)
s = int32(s);
b_id = -1;
rows = size(s,1);
flag = 0;
index = 1;

while true
    if index == 1
        data = s(index,1:7);
        flag = 1;
        index = index + 1;
        continue;
    else if index == rows
          data = [data;s(index,1:7)];
          n = node(data);
          father_id = findFatherAsSwc(n.data,b_id);
          insertSwcNode(n,father_id);
          break;
        end
    end
    if flag == 0 && s(index,7) ~= s(index-1,1)
            data = s(index,1:7);
            flag = 1;
            index = index + 1;
            continue;
        else if flag == 1 && s(index,7) ~= s(index-1,1)
                
                
                n = node(data);
                father_id = findFatherAsSwc(n.data,b_id);
                insertSwcNode(n,father_id);
                b_id = n.id;
                flag = 0;
                continue;
            end
    end
    data = [data;s(index,1:7)];
    index = index + 1;
end
  
end