// tiff_test.cpp : 定义控制台应用程序的入口点。
//

#include "stdafx.h"
#include <tiffio.h>
#include <iostream>
#include <stdio.h>
#include <time.h>
#include <math.h>
using namespace std;

uint32 myFloor(uint32 x, uint32 y){
    uint32 result = x / y;
    if(result * y < x){
        result ++;
    }
    return result;
}




int _tmain(int argc, _TCHAR* argv[])
{
    srand((unsigned short)time(NULL));
    TIFF *tiff1 = TIFFOpen("5.tif", "w");
    char *artist= "eeeee";
    unsigned short *content = new unsigned short[100 * 100];
    cout<<TIFFSetField(tiff1, TIFFTAG_ARTIST, "SSSSS")<<endl;
    cout<<TIFFGetField(tiff1, TIFFTAG_ARTIST, &artist)<<endl;
    cout<<TIFFSetField(tiff1, TIFFTAG_SAMPLESPERPIXEL, 1)<<endl;
    cout<<TIFFSetField(tiff1, TIFFTAG_IMAGEWIDTH, 100)<<endl;
    cout<<TIFFSetField(tiff1, TIFFTAG_IMAGELENGTH, 100)<<endl;
    cout<<TIFFSetField(tiff1, TIFFTAG_BITSPERSAMPLE, 16)<<endl;
    cout<<TIFFSetField(tiff1, TIFFTAG_ROWSPERSTRIP, 100)<<endl;
    cout<<TIFFSetField(tiff1, TIFFTAG_PLANARCONFIG, 1)<<endl;
    cout<<TIFFSetField(tiff1, TIFFTAG_COMPRESSION, 1)<<endl;
    cout<<TIFFSetField(tiff1, TIFFTAG_SUBFILETYPE, FILETYPE_PAGE)<<endl;
    cout<<TIFFSetField(tiff1, TIFFTAG_PAGENUMBER, 0)<<endl;
    TIFFSetField(tiff1, TIFFTAG_ORIENTATION, ORIENTATION_TOPLEFT);
    
    cout<<TIFFSetField(tiff1, TIFFTAG_PHOTOMETRIC, PHOTOMETRIC_MINISBLACK)<<endl;
    cout<<artist<<endl;        
    TIFFSetDirectory(tiff1, 0);
    for(int i = 0; i < 100; i ++){
        for(int j = 0; j < 100; j ++){
            content[i * 100 + j] = rand();   
        }
    }
    cout<<TIFFWriteEncodedStrip(tiff1, 0, content, 100 * 100 * 2)<<endl;
    cout<<TIFFWriteDirectory(tiff1)<<endl;
    cout<<TIFFSetField(tiff1, TIFFTAG_ARTIST, "EEEEE")<<endl;
    cout<<TIFFGetField(tiff1, TIFFTAG_ARTIST, &artist)<<endl;
    cout<<TIFFSetField(tiff1, TIFFTAG_SAMPLESPERPIXEL, 1)<<endl;
    cout<<TIFFSetField(tiff1, TIFFTAG_IMAGEWIDTH, 100)<<endl;
    cout<<TIFFSetField(tiff1, TIFFTAG_IMAGELENGTH, 100)<<endl;
    cout<<TIFFSetField(tiff1, TIFFTAG_BITSPERSAMPLE, 16)<<endl;
    cout<<TIFFSetField(tiff1, TIFFTAG_ROWSPERSTRIP, 100)<<endl;
    cout<<TIFFSetField(tiff1, TIFFTAG_PLANARCONFIG, 1)<<endl;
    cout<<TIFFSetField(tiff1, TIFFTAG_COMPRESSION, 1)<<endl;
    TIFFSetField(tiff1, TIFFTAG_ORIENTATION, ORIENTATION_TOPLEFT);
    cout<<TIFFSetField(tiff1, TIFFTAG_SUBFILETYPE, FILETYPE_PAGE)<<endl;
    cout<<TIFFSetField(tiff1, TIFFTAG_PAGENUMBER, 1)<<endl;    
    cout<<TIFFSetField(tiff1, TIFFTAG_PHOTOMETRIC, PHOTOMETRIC_MINISBLACK)<<endl;
    for(int i = 0; i < 100; i ++){
        for(int j = 0; j < 100; j ++){
            content[i * 100 + j] = rand();   
        }
    }
    cout<<artist<<endl;   
    cout<<TIFFWriteEncodedStrip(tiff1, 0, content, 100 * 100 * 2)<<endl;       
    TIFFClose(tiff1);
    //cout<<TIFFGetField(tiff1, TIFFTAG_IMAGEWIDTH)<<endl;
    //cout<<TIFFGetField(tiff1, OFILETYPE_PAGE)<<endl;
    cin.get();
	return 0;
}



    
    
    
    //    TIFF *tiff1 = TIFFOpen("5.tif", "r");
    //char *artist;
    //uint16 channals(0);
    //uint32 width(0);
    //uint32 height(0);
    //uint16 bits(0);
    //uint16 orientation(0);
    //uint32  rows_in_strip(0);
    //cout<<TIFFGetField(tiff1, TIFFTAG_ARTIST, &artist)<<endl;
    //cout<<TIFFGetField(tiff1, TIFFTAG_SAMPLESPERPIXEL, &channals)<<endl;
    //cout<<TIFFGetField(tiff1, TIFFTAG_IMAGEWIDTH, &width)<<endl;
    //cout<<TIFFGetField(tiff1, TIFFTAG_IMAGELENGTH, &height)<<endl;
    //cout<<TIFFGetField(tiff1, TIFFTAG_BITSPERSAMPLE, &bits)<<endl;
    //cout<<TIFFGetField(tiff1, TIFFTAG_ROWSPERSTRIP, &rows_in_strip)<<endl;
    //cout<<TIFFGetField(tiff1, TIFFTAG_ORIENTATION, &orientation)<<endl; 
    //cout<<"Artist: "<<artist<<endl;
    //cout<<"Image channals: "<<channals<<endl;
    //cout<<"Image width: "<<width<<endl;
    //cout<<"Image height: "<<height<<endl;
    //cout<<"Image depth: "<<bits<<endl;
    //cout<<"Rows in one strip: "<<rows_in_strip<<endl;
    //cout<<"Image orientation: "<<orientation<<endl;
    //unsigned short *image1 = new unsigned short[width * height];
    //uint32 strip_num(0);
    //strip_num = myFloor(height, rows_in_strip);
    //cout<<strip_num<<endl;
    //uint32 total_size = width * height * bits / 8;
    //uint32 readed_size(0);
    //for(uint32 i = 0; i < strip_num; i ++){
    //    cout<<i<<endl;
    //    uint32 read_size(0);
    //    if(i ==strip_num - 1){
    //        read_size = total_size - readed_size;
    //    }else{
    //        read_size = rows_in_strip * height * bits / 8;
    //    }
    //    TIFFReadEncodedStrip(tiff1, i, &image1[readed_size / 2], read_size);
    //    readed_size += read_size;
    //}
    //cout<<image1[1]<<endl;
    //
    //
    //TIFFClose(tiff1);