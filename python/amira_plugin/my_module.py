import ctypes
import os
import ImageGrab
import numpy as np
import cv2 as cv

class Ref_used():
    def __init__(self):
        self.txt_name = ""
        self.im = 0
        self.note = ""
        self.cord = ""
 
    def capture_raw(self):
        try:
            dll = ctypes.cdll.LoadLibrary('CameraDll.dll')
        except  Exception:
            print "Dll load error"
        else:
            try:
                print "aaaa"
                dll.CameraSubArea(0)
            except Exception:
                ref_images = []
                for i in xrange(10):
                    this_name = "./src/ref/%d.tif"%i
                    this_ref_image = cv.imread(this_name, cv.CV_LOAD_IMAGE_UNCHANGED)
                    ref_images.append(this_ref_image)
                record_txt = open(self.txt_name, 'a')
                image1 = ImageGrab.grabclipboard()
                self.im = np.array(image1)           
                image1 = self.im
                cv.imwrite("./src/raw.tif", image1)   
                retval, image1 = cv.threshold(image1, 50, 255, cv.THRESH_BINARY)
                image1 = cv.cvtColor(image1, cv.COLOR_BGR2GRAY)
                image1 = image1 > 10
                image1 = image1.astype(np.uint8)
                image1 = image1 * 255
                cv.imwrite("./src/bin.tif", image1)         
                flag_in = False
                s = 0
                block_num = 0
                char_num_array = []
                for i in xrange(image1.shape[0]):
                    if np.all(image1[i, :] == 255):
                        if flag_in:
                            flag_in = False
                            block = image1[s: i, :]
                            block_name = "./src/%d_block.tif"%block_num
                            char_num = 0
                            s_char = 0
                            flag_block = False
                            for j in xrange(block.shape[1]):
                                if np.all(block[:, j] == 255):
                                    if flag_block:
                                        flag_block = False
                                        char_block = block[:, s_char : j]
                                        char_name = "./src/char_%d_%d.tif"%(block_num, char_num)
                                        cv.imwrite(char_name, char_block)
                                        char_num += 1
                                else:
                                    if not flag_block:
                                        s_char = j
                                        flag_block = True            
                            cv.imwrite(block_name, block)
                            char_num_array.append(char_num)
                            block_num += 1
                    else:
                        if not flag_in:
                            s = i
                            flag_in = True
                   
                for i in xrange(block_num):
                    char_num = char_num_array[i]
                    this_record = ""
                    for j in xrange(char_num):
                        char_name = "./src/char_%d_%d.tif"%(i, j)
                        this_char_image = cv.imread(char_name, cv.CV_LOAD_IMAGE_UNCHANGED)
                        for k in xrange(10):         
                            if np.all(this_char_image == ref_images[k]):
                                this_record += str(k)
                    record_txt.write(this_record + "\t")
                    self.cord += this_record + "\t"
                record_txt.write(self.note)
                record_txt.write("\n\r")  
                record_txt.close()
        return
 
    def getname(self):
        pc_name = ctypes.c_char_p("".encode("utf-8"))
        pc_size = 16
        pc_name = ctypes.cast(pc_name, ctypes.c_char_p)
        try:
            ctypes.windll.kernel32.GetComputerNameA(pc_name, ctypes.byref(ctypes.c_int(pc_size)))
        except Exception:
                print "sth wrong"
        print pc_name.value.decode('utf-8')
 
def capture():
    getname()
    capture_raw()
 
 
def getClipBoardImage():
    im = ImageGrab.grabclipboard()  
    if isinstance(im, Image.Image):  
        print im.format, im.size, im.mode  
        width, height = im.size  
        pix = im.load()
        im_array = np.array(im)
    else:  
        pass    
    return im


def my_input():
    a = raw_input()
    print a