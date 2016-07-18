/********************************************************************
	created:	2016/07/09
	created:	9:7:2016   15:33
	filename: 	g:\sulei\workplace\c++\preprocessor\preprocessor\Worker.h
	file path:	g:\sulei\workplace\c++\preprocessor\preprocessor
	file base:	Worker
	file ext:	h
	author:		Su Lei
	
	purpose:	Essensial functions for Image Preprocessor
*********************************************************************/

#ifndef WORKER_H
#define WORKER_H

#include <cv.h>
#include <highgui.h>
#include <iostream>
#include <string>
#include <vector>
#include <sstream>
#include "Tar.h"
#include <omp.h>
#include <io.h>
#include <direct.h>
using namespace std;

class ParaOfPre{
public:
    ParaOfPre();
    ~ParaOfPre();
    string tar_src;
    string tar_dst;
    string tar_file_pre;
    string tar_file_post;
    unsigned int x_beg;
    unsigned int x_end;
    unsigned int y_beg;
    unsigned int y_end;
    unsigned int block_width;
    unsigned int block_height;
    string mon_src;
    string mon_dst;
    string mon_in_pre;
    string mon_in_post;
    string mon_out_pre;
    string mon_out_post;
    string pro_src;
    string pro_dst;
    string pro_in_pre;
    string pro_in_post;
    string pro_out_pre;
    string pro_out_post;
    string crop_src;
    string crop_dst;
    string crop_in_pre;
    string crop_in_post;
    string crop_out_pre;
    string crop_out_post;
    string res_src;
    string res_dst;
    string res_in_pre;
    string res_in_post;
    string res_out_pre;
    string res_out_post;
    string auto_src;
    string auto_dst;
    double res_fx;
    double res_fy;
    string sys_del;
    unsigned int crop_x, crop_y, crop_w, crop_h;
    unsigned int pro_thick;
    unsigned int process_num;
    unsigned int serial_beg;
    unsigned int serial_end;
    unsigned int serial_bits;
    unsigned int image_depth;
    unsigned int thread_num;
};

class Preprocessor{
public:
    Preprocessor(int t, ParaOfPre p);
    ~Preprocessor();
    void run();
    void SetPreType(int arg){pre_type = arg;}
    void SetParaOfPre(ParaOfPre arg){para = arg;}
    
    
private:
    int buildWorkGroup();
    int tar();
    int montage();
    int project();
    int crop();
    int resize();
    int autoWork();
    int groupProject();
    
    vector<vector<unsigned int>> workPool;
    int pre_type;
    ParaOfPre para;
    Preprocessor(const Preprocessor &);
    void operator=(const Preprocessor &);    
};

#endif