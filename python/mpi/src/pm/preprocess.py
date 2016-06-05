import sys
import os
import tarfile
import cv2
import numpy as np


class Preprocess():
    def __init__(self, filename):
        self.data = Data_info(filename)
        self.detar_file = self.data.dst + '\\'  + 'src'
        self.montage_file = self.data.dst + '\\'  + 'montage'
        self.projection_file = self.data.dst + '\\'  + 'projection'
        self.resample_file = self.data.dst + '\\'  + 'resample'
        self.tasks = None
    
    def make_file(self):
        detar_file_name = self.data.dst + '\\' + 'src'
        montage_file_name = self.data.dst + '\\' + 'montage'
        projection_file_name = self.data.dst + '\\'  + 'projection'
        resample_file_name = self.data.dst + '\\'  + 'resample' 
        if os.path.exists(self.data.dst):
            os.mkdir(detar_file_name)
            os.mkdir(montage_file_name)
            if self.data.is_projection:
                os.mkdir(projection_file_name)
            if self.data.is_resampling:
                os.mkdir(resample_file_name)
            return True
        else:
            return False
    
    def allocate_task(self):
        begin_num = self.data.begin_num
        end_num = self.data.end_num
        is_projection = self.data.is_projection
        process_num = self.data.process_num
        thickness = self.data.thick_projection
        self.tasks = [[]] * process_num
        if is_projection == False:
            thickness = 1
        total_task_num = end_num - begin_num + 1
        projection_fraction_num = (total_task_num + thickness - 1) / thickness
        node_fraction_num = (projection_fraction_num) / process_num
        task_num_for_each_node = [node_fraction_num * thickness] * process_num
        for i in xrange(projection_fraction_num - (node_fraction_num * process_num)):
            task_num_for_each_node[i] += thickness
        index = 0
        for i in xrange(process_num):            
            tmp_task_set = []
            for k in xrange(task_num_for_each_node[i]):               
                tmp_task_set.append(begin_num + index)
                if begin_num + index == end_num:
                    break
                index += 1
            self.tasks[i] = tmp_task_set
    
    def get_task_set(self, r):
        self.allocate_task()
        return self.tasks[r]
    
    def do_detar(self, task):
        if len(task) == 0:
            return
        file_pre = ''
        file_post = '.tar'
        src = self.data.src
        dst = self.detar_file
        for i in xrange(len(task)):
            n = task[i]
            file_name = src + '\\' + file_pre + "%05d"%n + file_post
            tar = tarfile.open(file_name)
            names = tar.getnames()
            for name in names:
                tar.extract(name, dst + '\\')
            tar.close()
    
    def do_montage(self, task):
        if len(task) == 0:
            return
        src = self.detar_file
        readPre = self.data.pre_frame
        readPost = self.data.post_frame
        dst = self.montage_file
        writePre = "test_"
        writePost = "_mon.tif"
        xBeg = self.data.frame_info[0]
        xEnd = self.data.frame_info[1]
        yBeg = self.data.frame_info[2]
        yEnd = self.data.frame_info[3]
        isReverse = 1
        numStr = "%05d"%(task[0])
        xStr = "%d"%(xBeg)
        yStr = "%d"%(yBeg)
        filename = src + '\\' + numStr + "\\" + readPre + numStr +"_" + xStr + "_" + yStr + readPost
        subimg = cv2.imread(filename,cv2.CV_LOAD_IMAGE_UNCHANGED)
        xWidth = subimg.shape[0]
        yWidth = subimg.shape[1]
        if self.data.image_depth == 8:
            img = np.zeros((subimg.shape[0]*(yEnd-yBeg+1),subimg.shape[1]*(xEnd-xBeg+1)),np.uint8)
        elif self.data.image_depth == 16:
            img = np.zeros((subimg.shape[0]*(yEnd-yBeg+1),subimg.shape[1]*(xEnd-xBeg+1)),np.uint16)
        for z in range(len(task)):
            s = task[z]
            numStr = "%05d"%(s)
            print "processing " + dst + "\\" + writePre + numStr + writePost
            for i in xrange(yBeg,yEnd+1):
                for j in xrange(xBeg,xEnd+1):
                    yStr = "%d"%(i)
                    xStr = "%d"%(j)
                    filename = src + "\\" + numStr + "\\" + readPre + numStr + "_" + xStr + "_" + yStr + readPost    
                    subimg = cv2.imread(filename,cv2.CV_LOAD_IMAGE_UNCHANGED)
                    if isReverse == 0:
                        img[(i-yBeg)*xWidth:(i+1-yBeg)*xWidth,(j-xBeg)*yWidth:(j+1-xBeg)*yWidth] = subimg
                    if isReverse == 1:
                        subimg = subimg[:,::-1]
                        img[(i-yBeg)*xWidth:(i+1-yBeg)*xWidth,(j-xBeg)*yWidth:(j+1-xBeg)*yWidth] = subimg
            z_ratio_rec = self.data.reciprocal_scale[2]
            if self.data.is_resampling == True and (((z - task[0]) % z_ratio_rec) == 0):
                raw_width = img.shape[0]
                raw_height = img.shape[1]
                x_ratio = 1.0 / self.data.reciprocal_scale[0]
                y_ratio = 1.0 / self.data.reciprocal_scale[1]
                re_width = int(raw_width * x_ratio)
                re_height = int(raw_height * y_ratio)
                re_image = cv2.resize(img, (re_height, re_width))
                cv2.imwrite(self.resample_file + '\\' + "test_" + numStr + '_res.tif', re_image)              
            cv2.imwrite(dst + "\\" + writePre + numStr + writePost,img)
    
    def do_projection(self, task):
        if len(task) == 0:
            return
        src = self.montage_file
        dst = self.projection_file
        readPre = "test_"
        readPost = "_mon.tif"
        writePre = "test_"
        wirtePost = "_pro.tif"
        blockNum = self.data.thick_projection
        sA = task
        for j in range(0,len(sA), blockNum):
            s = j
            e = j + blockNum - 1    
            if e > len(sA)-1:
                e = len(sA)-1
            print "process begin: %05d  end : %05d"%(sA[s], sA[e])
            sS = "%05d"%(sA[s])
            eS = "%05d"%(sA[e])
            for i in range(s, e+1):
                n = sA[i]
                numStr = "%05d"%(n)
                filename = src + '\\' + readPre+numStr+readPost
                if i == s:
                    print filename
                    img1 = cv2.imread(filename,cv2.CV_LOAD_IMAGE_UNCHANGED)
                    if self.data.image_depth == 8:
                        img3 = np.zeros(img1.shape,np.uint8)
                    elif self.data.image_depth == 16:
                        img3 = np.zeros(img1.shape,np.uint16)
                else:
                    img1 = cv2.imread(filename,cv2.CV_LOAD_IMAGE_UNCHANGED)
                img3 = np.maximum(img1,img3)
            print dst + '\\' + writePre + sS + "-" + eS + wirtePost
            cv2.imwrite(dst + ' \\' +writePre+sS+"-"+eS+wirtePost,img3)
    
        



class Data_info():
    def __init__(self, filename):
        self.filename = filename
        self.nodes_names = None
        self.process_num = -1
        self.src = None
        self.dst = None
        self.image_depth = -1
        self.begin_num = -1
        self.end_num = -1
        self.is_projection = -1
        self.thick_projection = -1
        self.is_resampling = -1
        self.reciprocal_scale = None
        self.frame_info = None
        self.pre_frame = None
        self.post_frame = None
        self.get_info()
    
    def get_info(self):
        data_file = open(self.filename, 'r')
        i = 0
        for line in data_file:
            if i == 1:
                self.nodes_names = line.strip()
            if i == 3:
                self.process_num = int(line.strip())
            if i == 5:
                self.src = line.strip()
            if i == 7:
                self.dst = line.strip()
            if i == 9:
                self.image_depth = int(line.strip())
            if i == 11:
                self.begin_num = int(line.strip())
            if i == 13:
                self.end_num = int(line.strip())
            if i == 15:
                self.is_projection = bool(int(line.strip()))
            if i == 17:
                self.thick_projection = int(line.strip())
            if i == 19:
                self.is_resampling = bool(int(line.strip()))
            if i == 21:
                self.reciprocal_scale = [int(j) for j in line.strip().split(' ')]
            if i == 23:
                self.frame_info = [int(k) for k in line.strip().split(' ')]
            if i == 25:
                self.pre_frame = line.strip()
            if i == 27:
                self.post_frame = line.strip()
            i += 1
        data_file.close()