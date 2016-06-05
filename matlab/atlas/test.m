clc;
clear all;
% Download and unzip the atlasVolume and annotation zip files

% 25 micron volume size
size = [528 320 456];
% VOL = 3-D matrix of atlas Nissl volume
fid = fopen('atlasVolume/atlasVolume.raw', 'r', 'l' );
VOL = fread( fid, prod(size), 'uint8' );
fclose( fid );
VOL = reshape(VOL,size);
% ANO = 3-D matrix of annotation labels
fid = fopen('annotation.raw', 'r', 'l' );
ANO = fread( fid, prod(size), 'uint32' );
fclose( fid );
ANO = reshape(ANO,size);

% Display one coronal section
% figure;imagesc(squeeze(VOL(100,:,:)));colormap(gray);
% figure;imagesc(squeeze(ANO(100,:,:)));colormap(lines);

% Display one sagittal section
% figure;imagesc(squeeze(ANO(:,:,220)));colormap(lines);
% figure;imagesc(squeeze(VOL(:,:,220)));colormap(gray);

dst = 'W:\lsu\TDI11302020\red\Allen_Nissl\';
% for i = 1 : 528 
%     a = squeeze(VOL(i,:,:));
%     b = uint8(a);
%     s = num2str(i, '%05d');
%     t = Tiff([dst s '.tif'], 'w');
%     t.setTag('Photometric',Tiff.Photometric.MinIsBlack);
%     t.setTag('Compression',Tiff.Compression.None);
%     t.setTag('BitsPerSample',8);
%     t.setTag('SamplesPerPixel',1);
%     t.setTag('SampleFormat',Tiff.SampleFormat.UInt);
%     t.setTag('ExtraSamples',Tiff.ExtraSamples.Unspecified);
%     t.setTag('ImageLength',320);
%     t.setTag('ImageWidth',456);
%     t.setTag('PlanarConfiguration',Tiff.PlanarConfiguration.Chunky);
%     t.write(b);
%     t.close();
end