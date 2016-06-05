#!/bin/bash
readPre="/lustre/share/Public/mostPreprocess/MBA-GF13004_compress/resample10x/test_"
readPost=".tif"
writePre="/lustre/share/Public/mostPreprocess/TDI036/ldaSrc/test_"
for i in `seq 18 845`;do
	index=$(printf "%05d" ${i})	
	readName=${readPre}${index}${readPost}
	writeName=${writePre}${index}${readPost}
	echo "remove "${readName}
	rm ${readName}
done
