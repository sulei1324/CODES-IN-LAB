from wand.api import library
import wand.color
import wand.image
import os
import multiprocessing as mpg

def trans(name, src, dst):
    print name, os.getpid()
    svg_file = open(src + "\\" + name)
    print svg_file
    svg_id = name[0 : len(name) - 4]
    with wand.image.Image() as image:
        with wand.color.Color('snow') as background_color:
            library.MagickSetBackgroundColor(image.wand,
                                             background_color.resource)
        image.read(blob=svg_file.read())
        png_image = image.make_blob("png32")
 
    with open(dst + '\\' + svg_id + ".png", "wb") as out:
        out.write(png_image)    


if __name__ == "__main__":
    pool = mpg.Pool(processes=6)
    src = r"G:\sulei\workplace\atlas\dst\svgs0"
    dst = r"G:\sulei\workplace\atlas\dst\pngs0"
    svg_num_files = os.listdir(src)
    
    for i in os.listdir(src):
        pool.apply_async(func=trans, args=(i, src, dst))
    
    pool.close()
    pool.join()
    
    print "All Done!"


