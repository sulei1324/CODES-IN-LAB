from tifffile import *

with TiffFile('00001.tif') as tif:
    images = tif.asarray()
    n = 0
    for page in tif:
        print n
        for tag in page.tags.values():
             t = tag.name, tag.value
             print t
        n += 1
 