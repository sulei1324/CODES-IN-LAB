#include "stdafx.h"
#include "mostdReader.h"


Mostd::Mostd(): 
    bits_num(8),
    mostd_src("test"),
    ROIData(0),
    piece(512),
    suf(".tif")
{
    
}

Mostd::Mostd(const char *src, const unsigned int bits): 
    bits_num(bits),
    mostd_src(src),
    ROIData(0),
    piece(512),
    suf(".tif")
{

}


Mostd::~Mostd(){
    delete []ROIData;
}

bool Mostd::setROI(const u_int roi[6])
{
    x_beg = roi[0];
    x_end = roi[1];
    y_beg = roi[2];
    y_end = roi[3];
    z_beg = roi[4];
    z_end = roi[5];
    if(x_end < x_beg || y_end < y_beg || z_end < z_beg){
        return false;
    }else if(x_beg < 0 || y_beg <0 || z_beg <0){
        return false;
    }else if((x_end > (whole_w - 1)) || (y_end > (whole_h - 1)) || (z_end > (whole_t - 1))){
        return false;
    }
    return true;
}

bool Mostd::setROI(u_int x_b, u_int x_e, u_int y_s, u_int y_e, u_int z_s, u_int z_e){
    x_beg = x_b;
    x_end = x_e;
    y_beg = y_s;
    y_end = y_e;
    z_beg = z_s;
    z_end = z_e;
    if(x_end < x_beg || y_end < y_beg || z_end < z_beg){
        return false;
    }else if(x_beg < 0 || y_beg <0 || z_beg <0){
        return false;
    }else if((x_end > (whole_w - 1)) || (y_end > (whole_h - 1)) || (z_end > (whole_t - 1))){
        return false;
    }
    return true;
}

bool Mostd::loadMostd(){
    fstream f("test.mostd", ios::in);
    if(f.fail()){
        return false;
    }
    char line[512];
    int i = 1;
    while(!f.eof()){
        if(i == 34){
            f>>level_image_src;
        }else if(i == 3){
            f>>whole_w;
        }else if(i == 4){
            f>>whole_h;
        }else if(i == 5){
            f>>whole_t;
        }else if(i == 31){
            f>>x_res;
        }else if(i == 32){
            f>>y_res;
        }else if(i == 33){
            f>>z_res;
        }else{
            f>>line;
        }
        ++i;  
    }
    return true;
}

bool Mostd::loadImages(){
    u_int z_b1 = z_beg / piece;
    u_int z_b2 = z_end / piece;
    u_int y_b1 = y_beg / piece;
    u_int y_b2 = y_end / piece;
    u_int x_b1 = x_beg / piece;
    u_int x_b2 = x_end / piece;
    u_int w = x_end - x_beg + 1;
    u_int h = y_end - y_beg + 1;
    u_int t = z_end - z_beg + 1;
    cout<<w<<" "<<h<<" "<<t<<endl;
    u_int z_b_s, z_b_e, y_b_s, y_b_e, x_b_s, x_b_e;
    u_int z_o_s, z_o_e, y_o_s, y_o_e, x_o_s, x_o_e;      
    ROIData = new u_short[w * h * t];
    string image_src(level_image_src);
    stringstream s;
    int t_i = 1;
    for(u_int i = z_b1; i <= z_b2; ++i){
        if(i == z_b1){
            z_b_s = z_beg - z_b1 * piece;
        }else{
            z_b_s = 0;
        }
        if(i == z_b2){
            z_b_e = z_end - z_b2 * piece;
        }else{
            z_b_e = 511;
        }
        if(i == z_b1){
            z_o_s = 0;
        }else{
            z_o_s = z_o_e + 1;
        }
        if(i == z_b2){
            z_o_e = t - 1;
        }else{
            z_o_e = z_o_s + z_b_e - z_b_s;
        }
        for(u_int j = y_b1; j <= y_b2; ++j){
            if(j == y_b1){
                y_b_s = y_beg - y_b1 * piece;
            }else{
                y_b_s = 0;
            }
            if(j == y_b2){
                y_b_e = y_end - y_b2 * piece;
            }else{
                y_b_e = 511;
            }
            if(j == y_b1){
                y_o_s = 0;
            }else{
                y_o_s = y_o_e + 1;
            }
            if(j == y_b2){
                y_o_e = h - 1;
            }else{
                y_o_e = y_o_s + y_b_e - y_b_s;
            } 
            for(u_int k = x_b1; k <= x_b2; ++k){
                if(k == x_b1){
                    x_b_s = x_beg - x_b1 * piece;
                }else{
                    x_b_s = 0;
                }
                if(k == x_b2){
                    x_b_e = x_end - x_b2 * piece;
                }else{
                    x_b_e = 511;
                } 
                if(k == x_b1){
                    x_o_s = 0;
                }else{
                    x_o_s = x_o_e + 1;
                }
                if(k == x_b2){
                    x_o_e = w - 1;
                }else{
                    x_o_e = x_o_s + x_b_e - x_b_s;
                }                      
                //cout<<"z"<<i<<"\\y"<<j<<"\\"<<k<<"_"<<j<<"_"<<i<<suf<<endl;
                //cout<<x_o_s<<" "<<x_o_e<<" "<<x_b_s<<" "<<x_b_e<<endl;
                //cout<<y_o_s<<" "<<y_o_e<<" "<<y_b_s<<" "<<y_b_e<<endl;
                //cout<<z_o_s<<" "<<z_o_e<<" "<<z_b_s<<" "<<z_b_e<<endl;
                u_short *single_slice = new u_short[w * h];
                string image_name(image_src + "\\level1_data\\");
                s<<"z"<<i<<"\\y"<<j<<"\\"<<k<<"_"<<j<<"_"<<i<<suf;
                image_name.append(s.str());
                s.clear();
                s.str("");
                cout<<image_name<<endl;
                TIFFSetWarningHandler(0);
                TIFF *tif = TIFFOpen(image_name.c_str(), "r");
                uint16 bitsPerPixel(0);    
                if(tif == 0){
                    cout<<"Read Tif Error!"<<endl;
                    return false;
                }
                TIFFGetField(tif, TIFFTAG_BITSPERSAMPLE, &bitsPerPixel);
                u_int a_strip_bytes_num = piece * piece * bitsPerPixel / 8;
                TIFFSetDirectory(tif, z_b_s);
                for(u_int del_z = z_b_s - z_b_s; del_z <= z_b_e - z_b_s; ++del_z){
                    if(TIFFReadEncodedStrip(tif, 0, single_slice, a_strip_bytes_num) != -1){
                        for(u_int del_y = y_b_s - y_b_s; del_y <= y_b_e - y_b_s; ++del_y){
                            for(u_int del_x = x_b_s - x_b_s; del_x <=x_b_e - x_b_s; ++ del_x){
                                ROIData[(z_o_s + del_z) * (w * h) +  (y_o_s + del_y) * w + (x_o_s + del_x)] = single_slice[(y_b_s + del_y) * piece + (x_b_s + del_x)];
                            }
                        }
                    }else{
                        cout<<"Read Strip Error!"<<endl;
                        return false;
                    }      
                    if(TIFFReadDirectory(tif)){
                        continue;   
                    }else{
                        break;
                    }
                }
                //if(t_i ==  1){
                //    uint16 tchannals(0);
                //    uint32 twidth(0);
                //    uint32 theight(0);
                //    uint16 tbits(0);
                //    uint16 torientation(0);
                //    uint32  trows_in_strip(0);
                //    cout<<TIFFGetField(tif, TIFFTAG_SAMPLESPERPIXEL, &tchannals)<<"Channals: "<<tchannals<<endl;             //1
                //    cout<<TIFFGetField(tif, TIFFTAG_IMAGEWIDTH, &twidth)<<"Width: "<<twidth<<endl;                                   //512
                //    cout<<TIFFGetField(tif, TIFFTAG_IMAGELENGTH, &theight)<<"Height: "<<theight<<endl;                              //512
                //    cout<<TIFFGetField(tif, TIFFTAG_BITSPERSAMPLE, &tbits)<<"Bits: "<<tbits<<endl;                                         //16 8
                //    cout<<TIFFGetField(tif, TIFFTAG_ROWSPERSTRIP, &trows_in_strip)<<"RowsInStrip: "<<trows_in_strip<<endl; //512
                //    cout<<TIFFGetField(tif, TIFFTAG_ORIENTATION, &torientation)<<"ORIENTATION: "<<torientation<<endl;     //1 top left
                //}
                //for(u_short l = z_b_s; l <= z_b_e; ++l){
                //    TIFFSetDirectory(tif, l);
                //
                //}
                TIFFClose(tif);
                t_i ++;
                
                
                
                
                
                
                
                
                
                
            }            
        
        
        
        }
        
        
        
        
    
    
    }




    return true;
}