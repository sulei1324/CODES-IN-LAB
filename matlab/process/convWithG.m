function [outImage]=convWithG(inImage,g)

% g radius=4*L+1 L=2*R+1

outImage=imfilter(inImage,g,'replicate');

end