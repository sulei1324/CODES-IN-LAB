#!/bin/bash
readPre="/lustre/share/Public/mostPreprocess/TDI036/montage/test_"
readPost="python.tif"
writePre="/lustre/share/Public/mostPreprocess/TDI036/ldaSrc/test_"
for i in `seq 1091 6430`;do
	index=$(printf "%05d" ${i})	
	readName=${readPre}${index}${readPost}
	writeName=${writePre}${index}${readPost}
	echo "cp "${readName}" to "${writeName}
	cp ${readName} ${writeName}
done
