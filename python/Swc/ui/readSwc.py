import numpy as np
import math
import readMostd
from copy import deepcopy
import vtk


class Swc():
    def __init__(self, filesrc, resolution):
        self.src = filesrc
        self.resolution = resolution
        self.lines = self.getLines(self.src)
        self.max_level = self.find_max_level(self.lines)
        self.fiber_length = self.get_total_fiber_length_in_swc(self.lines)
        self.line_num = len(self.lines)
        self.node_list = self.swc2list(self.src)
        self.node_coordinates = self.get_node_coordinates()
        self.roi = self.get_roi_of_swc()
        self.real_roi = self.get_real_roi()
        self.more_real_roi = self.get_more_roi()
        
    def displayInVtk(self):
        lines = self.lines
        lines_actors = []
        for i in xrange(len(lines)):   
            this_line = lines[i].data
            this_line_poly_data = vtk.vtkPolyData()
            this_line_points = vtk.vtkPoints()
            for i in xrange(len(this_line)):
                this_line_points.InsertPoint(i, this_line[i][2:5])
            this_line_cells = vtk.vtkCellArray()
            this_line_cells.InsertNextCell(len(this_line))
            for i in xrange(len(this_line)):
                this_line_cells.InsertCellPoint(i)          
            this_line_poly_data.SetPoints(this_line_points)
            this_line_poly_data.SetLines(this_line_cells)
            this_line_mapper = vtk.vtkPolyDataMapper()
            this_line_mapper.SetInput(this_line_poly_data)
            this_line_actor = vtk.vtkActor()
            this_line_actor.SetMapper(this_line_mapper)
            this_line_actor.GetProperty().SetLineWidth(5)
            lines_actors.append(this_line_actor)        
        ren = vtk.vtkRenderer()
        for i in lines_actors:
            ren.AddActor(i)
        ren.SetBackground(0.1, 0.2, 0.3)       
        renWin = vtk.vtkRenderWindow()
        renWin.AddRenderer(ren)
        iren = vtk.vtkRenderWindowInteractor()
        iren.SetRenderWindow(renWin)
        renWin.Render()
        iren.Start()        
        
    
    def trans_to_local_real_swc(self, used_roi, dst):
        x_d = used_roi[0]
        y_d = used_roi[1]
        z_d = used_roi[2]
 #       print x_d, y_d, z_d
        local_real_node_list = deepcopy(self.node_list)
        for i in xrange(len(local_real_node_list)):
#            print local_real_node_list[i][2]
            local_real_node_list[i][2] = local_real_node_list[i][2] / 0.3 - x_d
            local_real_node_list[i][3] = local_real_node_list[i][3] / 0.3 - y_d
            local_real_node_list[i][4] = local_real_node_list[i][4] - z_d
#            print local_real_node_list[i][2]
        self.outputSwc(local_real_node_list, dst + 'real_')
        
    
    def trans_to_local_swc(self, used_roi, isReal, dst):
        if isReal:
            ratio = self.resolution
        else:
            ratio = (1, 1, 1)
        x_d = used_roi[0] * ratio[0]
        y_d = used_roi[1] * ratio[1]
        z_d = used_roi[2] * ratio[2]
#        print x_d, y_d, z_d
        new_node_list = deepcopy(self.node_list)
        for i in  xrange(len(new_node_list)):
            new_node_list[i][2] -= x_d
            new_node_list[i][3] -= y_d
            new_node_list[i][4] -= z_d 
        self.outputSwc(new_node_list, dst)
        
        
    def outputSwc(self, swc_list, dst):
        path_str = self.src.split('\\')
        src_name = path_str[-1]
        f = open(dst + 'local_' + src_name, 'w')
        for i in xrange(len(swc_list)):
            out_str = " %d %d %f %f %f %f %d \n"%(swc_list[i][0], swc_list[i][1], swc_list[i][2], swc_list[i][3], swc_list[i][4], swc_list[i][5], swc_list[i][6])
            f.write(out_str)
        f.close()
        pass
    
    def get_real_roi(self):
        real_roi_xs = int(self.roi[0] / self.resolution[0])
        real_roi_ys = int(self.roi[1] / self.resolution[1])
        real_roi_zs = int(self.roi[2] / self.resolution[2])
        real_roi_w = int(self.roi[3] / self.resolution[0])
        real_roi_h = int(self.roi[4] / self.resolution[1])
        real_roi_d = int(self.roi[5] / self.resolution[2])
        return (real_roi_xs, real_roi_ys, real_roi_zs, real_roi_w, real_roi_h, real_roi_d)
        
    def get_more_roi(self):
        more_roi_xs = self.real_roi[0] - 15
        more_roi_ys = self.real_roi[1] - 15
        more_roi_zs = self.real_roi[2] - 5
        more_roi_w = self.real_roi[3] + 30
        more_roi_h = self.real_roi[4] + 30
        more_roi_d = self.real_roi[5] + 10
        return (more_roi_xs, more_roi_ys, more_roi_zs, more_roi_w, more_roi_h, more_roi_d)
    
    def get_roi_of_swc(self):
        x_coordinates = []
        y_coordinates = []
        z_coordinates = []
        roi = []
        for i in self.node_coordinates:
            x_coordinates.append(i[0])
            y_coordinates.append(i[1])
            z_coordinates.append(i[2])
        x_coordinates = np.array(x_coordinates)
        y_coordinates = np.array(y_coordinates)
        z_coordinates = np.array(z_coordinates)
        roi.append(int(np.min(x_coordinates)))
        roi.append(int(np.min(y_coordinates)))
        roi.append(int(np.min(z_coordinates)))
        roi.append(int(np.max(x_coordinates) - np.min(x_coordinates)) + 1)
        roi.append(int(np.max(y_coordinates) - np.min(y_coordinates)) + 1)
        roi.append(int(np.max(z_coordinates) - np.min(z_coordinates)) + 1)
        return roi  
    
    def get_node_coordinates(self):
        coordinates = []
        for i in self.node_list:
            coordinates.append(i[2:5])
        return coordinates
        
    def getLines(self, src):
        swc_list = self.swc2list(src)
        line_list = self.swc_list2line_list(swc_list)
        return line_list

    def swc2list(self, swc_src):
        swc_file = open(swc_src)
        swc_list = []
        for line in swc_file:
            tmp_node = []
            str_list_node_info = line.strip().split(' ')
            for i in xrange(len(str_list_node_info)):
                if i in [0, 1, 6]:
                    tmp_node.append(int(str_list_node_info[i]))
                else:
                    tmp_node.append(float(str_list_node_info[i]))  
            swc_list.append(tmp_node)
        return swc_list
    
    def swc_list2line_list(self, swc_list):
        self.clear_isolated_node(swc_list)
        line_list = []
        if len(swc_list) == 0:
            print "there is no node!"
            return None
        for i in xrange(len(swc_list)):
            if swc_list[i][6] == -1:
                tmp_line = []
                tmp_line.append(swc_list[i])
            elif swc_list[i][6] != swc_list[i][0] - 1:
                pre_node = swc_list[i][6]
                line = Line(tmp_line, line_list)
                line_list.append(line)
                tmp_line = []
                tmp_line.append(swc_list[pre_node])
                tmp_line.append(swc_list[i])
            else:
                tmp_line.append(swc_list[i])
            if i == len(swc_list) - 1:
                line = Line(tmp_line, line_list)
                line_list.append(line)
        return line_list
        
    def clear_isolated_node(self, swc_list):
        for i in xrange(len(swc_list) - 1, -1, -1):
            if swc_list[i][6] == -1:
                swc_list.pop()
            else:
                break
            
    def find_max_level(self, lines):
        max_level = 0
        for line_i in lines:
            if line_i.level > max_level:
                max_level = line_i.level
        return max_level
    
    def get_total_fiber_length_in_swc(self, lines):
        total_fiber_length_in_swc= 0
        for line_i in lines:
            total_fiber_length_in_swc += line_i.fiber_length
        return total_fiber_length_in_swc
    

        
        
    


class Line():
    def __init__(self, data, line_list):
        self.length = len(data)
        self.region_start = data[0][0]
        self.region_end = data[len(data) - 1][0]
        self.data = data
        self.points = data
        self.father = data[0][len(data[0]) - 1]
        self.father_in_line_list_location = self.find_father_in_line_list_location(line_list)
        self.level = self.count_level(line_list)
        self.fiber_length = self.count_fiber_length()
        
    def count_fiber_length(self):
        for i in range(self.length):
            if i == 0:
                pre_node = self.data[i]
                l = 0
                continue
            else:
                this_node = self.data[i]
                this_node_x = this_node[2]
                this_node_y = this_node[3]
                this_node_z = this_node[4]
                pre_node_x = pre_node[2]
                pre_node_y = pre_node[3]
                pre_node_z = pre_node[4]
                l += math.sqrt((this_node_x - pre_node_x) ** 2 + (this_node_y - pre_node_y) ** 2 + (this_node_z - pre_node_z) ** 2)
        return l
        
    
    def count_level(self, line_list):
        if self.father == -1:
            return 0
        else:
            return line_list[self.father_in_line_list_location].level + 1
    
    def find_father_in_line_list_location(self, line_list):
        if self.father == -1:
            return -1
        for i in xrange(len(line_list)):
            line_i = line_list[i]
            if self.father in range(line_i.region_start, line_i.region_end):
                return i
    
            







