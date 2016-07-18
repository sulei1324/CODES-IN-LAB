#include "stdafx.h"
#include <iostream>
#include "tiffio.h"
#include <fstream>
#include <sstream>
#include <string>
typedef unsigned int u_int;
typedef unsigned short u_short;   //16
typedef unsigned char u_char;  //8
using namespace std;

class Mostd{
public:
    Mostd();
    Mostd(const char *src, const u_int bits);
    ~Mostd();
    
    
    const char *mostd_src;
    const u_int bits_num;
    u_int x_beg;
    u_int x_end;
    u_int y_beg;
    u_int y_end;
    u_int z_beg;
    u_int z_end;
    bool setROI(const u_int roi[6]);
    bool setROI(u_int x_b, u_int x_e, u_int y_s, u_int y_e, u_int z_s, u_int z_e);
    u_short *ROIData;
    bool loadMostd();
    bool loadImages();

private:
    const u_int piece;
    const char *suf;
    u_int whole_w;
    u_int whole_h;
    u_int whole_t;
    string level_image_src;
    float x_res;
    float y_res;
    float z_res;
    
    
    
    
    
    
    


};


