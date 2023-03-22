clear all; close all;
clc

[IMG, MAP, ALPHA]=imread('mossy.png');

color=(uint32(IMG(:,:,1)) * 2^16 + uint32(IMG(:,:,2)) * 2^8 + uint32(IMG(:,:,3)))';

fname='textN';
fid=fopen(fname,'wb');
for i=1:numel(color)
  fwrite(fid, color(i), 'uint32');
end
i
fclose(fid);


%%%%%%%%%%%%%%%%
[IMG, MAP, ALPHA]=imread('greystone.png');

color=(uint32(IMG(:,:,1)) * 2^16 + uint32(IMG(:,:,2)) * 2^8 + uint32(IMG(:,:,3)))';

fname='textS';
fid=fopen(fname,'wb');
for i=1:numel(color)
  fwrite(fid, color(i), 'uint32');
end
i
fclose(fid);

%%%%%%%%%%%%%%%%
[IMG, MAP, ALPHA]=imread('wood.png');

color=(uint32(IMG(:,:,1)) * 2^16 + uint32(IMG(:,:,2)) * 2^8 + uint32(IMG(:,:,3)))';

fname='textW';
fid=fopen(fname,'wb');
for i=1:numel(color)
  fwrite(fid, color(i), 'uint32');
end
i
fclose(fid);

%%%%%%%%%%%%%%%%
[IMG, MAP, ALPHA]=imread('redbrick.png');

color=(uint32(IMG(:,:,1)) * 2^16 + uint32(IMG(:,:,2)) * 2^8 + uint32(IMG(:,:,3)))';

fname='textE';
fid=fopen(fname,'wb');
for i=1:numel(color)
  fwrite(fid, color(i), 'uint32');
end
i
fclose(fid);
