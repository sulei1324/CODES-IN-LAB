#include "stdafx.h"
#ifndef MOSTDREADER_H
#define MOSTDREADER_H
#include "SwcReader.h"
#include "tiffio.h"
#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv/highgui.h>
#include "ImageCache.h"
typedef unsigned int u_int;
typedef unsigned short u_short;   //16
typedef unsigned char u_char;  //8
using namespace std;

class Mostd{
public:
    Mostd();
    Mostd(const char *src, const u_int bits, const u_int numArg);
    ~Mostd();
    bool setROI(const u_int roi[6]);
    bool setROI(u_int x_b, u_int x_e, u_int y_s, u_int y_e, u_int z_s, u_int z_e);
    bool loadMostd();
    bool loadImages();
    bool showImages();
    void savaImages();
    u_short *GetImageData16();
    u_char *GetImageData8();
    vector<float>& GetResolution();
    vector<u_int> &GetRoi();
    static void cvOnMouse(int event, int x, int y, int flags, void* param);
    u_int curPage;
    u_int maxPage;
    u_int signleImagePixelCounts;
    u_int imageWidth;
    u_int imageHeight;
    u_int imageThick;
    const u_int bits_num;
    char *windowName;
    
private:
    bool loadImageFlag;
    const char *mostd_src;
    u_int x_beg;
    u_int x_end;
    u_int y_beg;
    u_int y_end;
    u_int z_beg;
    u_int z_end;
    u_short *ROIData16;
    u_char *ROIData8;
    const u_int piece;
    const char *suf;
    u_int whole_w;
    u_int whole_h;
    u_int whole_t;
    string level_image_src;
    float x_res;
    float y_res;
    float z_res;
    u_int cacheNum;
    ImageCaches imageCaches;
    vector<float> resolution;
    vector<u_int> roi;
    Mostd(const Mostd &);
    void operator=(const Mostd &); 
};
#endif




