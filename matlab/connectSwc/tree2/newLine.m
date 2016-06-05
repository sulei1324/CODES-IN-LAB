function line = newLine(p_s, p_e, p_data)
line = struct();
line.ps = p_s;
line.pe = p_e;
line.pdata = p_data;
line.length = getLength(line.pdata);
end