//#include <stdio.h>
#include "stdafx.h"
//#include <tiffio.h>
//#include <iostream>
//using namespace std;
//
//int main(){
//    TIFF* tif_read = TIFFOpen("1.tif", "r");
//    TIFF* tif_write = TIFFOpen("2.tif", "w");
//    int raw_width, raw_height, x_begin, y_begin, cropped_width, cropped_height;                    // raw_width = 864, raw_height = 540
//    x_begin = 40;
//    y_begin = 40;
//    cropped_width = 400;
//    cropped_height = 400;
//    int x_end = x_begin + cropped_width - 1;
//    int y_end = y_begin + cropped_height - 1;
//    uint16 bitspersample = 8;
//    uint16 photo=1;
//    uint16 samplesperpixel = 1;
//    unsigned char *tmp = new unsigned char[cropped_width * cropped_height];
//    int pixel_value;
//    int loop_index_1;
//    int loop_index_2;
//    int loop_index_3 = 0;
//    TIFFGetField(tif_read, TIFFTAG_IMAGEWIDTH, &raw_width);
//    TIFFGetField(tif_read, TIFFTAG_IMAGELENGTH, &raw_height);
//    TIFFGetField(tif_read, TIFFTAG_BITSPERSAMPLE, &bitspersample);
//    TIFFGetField(tif_read, TIFFTAG_PHOTOMETRIC, &photo); 
//    TIFFGetField(tif_read, TIFFTAG_SAMPLESPERPIXEL, &samplesperpixel);
//    
//    cout<<samplesperpixel<<endl;
//
//    //uint32* raster = new uint32[raw_width * raw_height];
//    //TIFFReadRGBAImageOriented(tif_read, raw_width, raw_height, raster, ORIENTATION_TOPLEFT);
//    //std::cout<<x_begin<<" "<<x_end<<std::endl;
//    //std::cout<<y_begin<<" "<<y_end<<std::endl;
//    //for(loop_index_1 = x_begin; loop_index_1 <= x_end; ++loop_index_1){
//    //    for(loop_index_2 = y_begin; loop_index_2 <= y_end; ++loop_index_2){
//    //        pixel_value = TIFFGetG(raster[loop_index_1 * raw_width + loop_index_2]);
//    //        tmp[loop_index_3] = (unsigned char)pixel_value;
//    //        loop_index_3 ++;        
//    //    }     
//    //}    
// 
//    //TIFFSetField(tif_write, TIFFTAG_PAGENUMBER, 0);
//    //TIFFSetField(tif_write, TIFFTAG_IMAGEWIDTH, (uint32)cropped_width);
//    //TIFFSetField(tif_write, TIFFTAG_IMAGELENGTH, (uint32)cropped_height);
//    //TIFFSetField(tif_write, TIFFTAG_ORIENTATION, ORIENTATION_TOPLEFT);
//    //TIFFSetField(tif_write, TIFFTAG_BITSPERSAMPLE, 8);
//    //TIFFSetField(tif_write, TIFFTAG_SAMPLESPERPIXEL, 1);
//    //TIFFSetField(tif_write, TIFFTAG_COMPRESSION, COMPRESSION_NONE);
//    //TIFFSetField(tif_write, TIFFTAG_PHOTOMETRIC, PHOTOMETRIC_MINISBLACK);
//    //TIFFSetField(tif_write, TIFFTAG_PLANARCONFIG, PLANARCONFIG_CONTIG);
//    //TIFFSetField(tif_write, TIFFTAG_ROWSPERSTRIP,cropped_height);
//    //TIFFWriteEncodedStrip(tif_write, 0, tmp, cropped_width * cropped_height);
//
//    TIFFClose(tif_read);
//    //TIFFClose(tif_write);
//    cin.get();
//
//}
