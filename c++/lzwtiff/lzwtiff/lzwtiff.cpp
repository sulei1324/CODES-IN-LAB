// lzwtiff.cpp : 定义控制台应用程序的入口点。
//

#include "stdafx.h"

#include <iostream>

#include <FreeImage.h>
#include <direct.h>
#include <string>
#include <sstream>
#include <iomanip>
#include <opencv2/highgui/highgui.hpp>
using std::cout;
using std::cin;
using std::endl;
using std::string;
using std::stringstream;
using std::setw;
using std::setfill;

int main(int argc, _TCHAR* argv[])
{
    FreeImage_Initialise(true);
    FREE_IMAGE_FORMAT fif = FIF_UNKNOWN;
    FIBITMAP *bitmap1 = 0;
    string src = "G:\\sulei\\workplace\\vs\\lzwtiff\\lzwtiff\\05578";
    string dst = "G:\\sulei\\workplace\\vs\\lzwtiff\\lzwtiff\\05578_lzw";
    string pre = "green__";
    string post = ".tif";
    int x_beg = 40;
    int x_end = 64;
    int y_beg = 31;
    int y_end = 54;
    int serial_num = 5578;
    string x_beg_str, x_end_str, y_beg_str, y_end_str, serial_str, image_name, this_x_str, this_y_str, dst_image_name, src_image_name;
    stringstream ss;
    ss<<setw(5)<<setfill('0')<<serial_num;
    serial_str = ss.str();
    int this_x, this_y;
    for(int i = x_beg; i <= x_end; i++){
        ss.str("");
        this_x = i;
        ss<<this_x;
        this_x_str = ss.str();
        for(int j = y_beg; j <= y_end; j++){
            ss.str("");
            this_y = j;
            ss<<this_y;
            this_y_str = ss.str();
            image_name = pre + serial_str + "_" + this_x_str + "_" + this_y_str + post;            
            src_image_name = src + "\\" + image_name;
            dst_image_name = dst + "\\" +pre + serial_str + "_" + this_x_str + "_" + this_y_str + ".tif";
            fif = FreeImage_GetFileType(src_image_name.c_str());
            bitmap1 = FreeImage_Load(fif, src_image_name.c_str());
            FreeImage_Save(fif, bitmap1, dst_image_name.c_str(), TIFF_LZW);
        }
    
    }
    FreeImage_DeInitialise();
	return 0;
}

