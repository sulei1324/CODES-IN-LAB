import Image

a = Image.open('1.tif')
print a.format, a.size, a.mode
a.show()