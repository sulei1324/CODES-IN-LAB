import numpy
import math
#import pylibtiff

image_resolution = [0.3, 0.3, 1]

class Line():
    def __init__(self, data, line_list):
        self.length = len(data)
        self.region_start = data[0][0]
        self.region_end = data[len(data) - 1][0]
        self.data = data
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
    
            
def swc2list(swc_file):
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
        

def swc_list2line_list(swc_list):
    line_list = []
    if len(swc_list) == 0:
        print "there is no node!"
        return None
    for i in xrange(len(swc_list)):
        if swc_list[i][6] == -1:
            tmp_line = []
            tmp_line.append(swc_list[i])
        elif swc_list[i][6] != swc_list[i][0] - 1:
            line = Line(tmp_line, line_list)
            line_list.append(line)
            tmp_line = []
            tmp_line.append(swc_list[i])
        else:
            tmp_line.append(swc_list[i])
        if i == len(swc_list) - 1:
            line = Line(tmp_line, line_list)
            line_list.append(line)
    return line_list

def clear_isolated_node(swc_list):
    for i in xrange(len(swc_list) - 1, -1, -1):
        if swc_list[i][6] == -1:
            swc_list.pop()
        else:
            break
        
def find_max_level(lines):
    max_level = 0
    for line_i in lines:
        if line_i.level > max_level:
            max_level = line_i.level
    return max_level

def get_total_fiber_length_in_swc(lines):
    total_fiber_length_in_swc= 0
    for line_i in lines:
        total_fiber_length_in_swc += line_i.fiber_length
    return total_fiber_length_in_swc
            
            
            
a = open("dendrite.swc");
node_list  = swc2list(a)
a.close()
clear_isolated_node(node_list)
line_list = swc_list2line_list(node_list)
max_level = find_max_level(line_list)
fiber_length = get_total_fiber_length_in_swc(line_list)
print max_level, fiber_length / 1000 / 1000

