#include "stdafx.h"
#include "mostdReader.h"


Mostd::Mostd(): 
    bits_num(8),
    mostd_src("test"),
    piece(512),
    ROIData8(0),
    ROIData16(0),
    suf(".tif"),
    loadImageFlag(false),
    curPage(0),
    maxPage(0),
    signleImagePixelCounts(0), 
    windowName("test")
{
    
}

Mostd::Mostd(const char *src, const unsigned int bits): 
    bits_num(bits),
    mostd_src(src),
    ROIData16(0),
    ROIData8(0),
    piece(512),
    suf(".tif"),
    loadImageFlag(false),
    curPage(0),
    maxPage(0),
    signleImagePixelCounts(0),
    windowName("test")
{
    
}


Mostd::~Mostd(){
    if(ROIData16){
        delete []ROIData16;
    }
    if(ROIData8){
        delete []ROIData8;
    }
}

bool Mostd::setROI(const u_int roi[6])
{
    x_beg = roi[0];
    x_end = roi[1];
    y_beg = roi[2];
    y_end = roi[3];
    z_beg = roi[4];
    z_end = roi[5];
    imageWidth = x_end - x_beg + 1;
    imageHeight = y_end - y_beg + 1;
    if(x_end < x_beg || y_end < y_beg || z_end < z_beg){
        return false;
    }else if(x_beg < 0 || y_beg <0 || z_beg <0){
        return false;
    }else if((x_end > (whole_w - 1)) || (y_end > (whole_h - 1)) || (z_end > (whole_t - 1))){
        return false;
    }
    signleImagePixelCounts = imageWidth * imageHeight;
    return true;
}

bool Mostd::setROI(u_int x_b, u_int x_e, u_int y_s, u_int y_e, u_int z_s, u_int z_e){
    x_beg = x_b;
    x_end = x_e;
    y_beg = y_s;
    y_end = y_e;
    z_beg = z_s;
    z_end = z_e;
    imageWidth = x_end - x_beg + 1;
    imageHeight = y_end - y_beg + 1;
    if(x_end < x_beg || y_end < y_beg || z_end < z_beg){
        return false;
    }else if(x_beg < 0 || y_beg <0 || z_beg <0){
        return false;
    }else if((x_end > (whole_w - 1)) || (y_end > (whole_h - 1)) || (z_end > (whole_t - 1))){
        return false;
    }
    signleImagePixelCounts = imageWidth * imageHeight;
    return true;
}

bool Mostd::loadMostd(){
    fstream f(mostd_src, ios::in);
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
    if(bits_num == 16){
        ROIData16 = new u_short[w * h * t];
        
    }else if(bits_num == 8){
        ROIData8 = new u_char[w * h * t];
    }
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
                int stripByteCounts = TIFFStripSize(tif);
                int stripNum = TIFFNumberOfStrips(tif);
                TIFFSetDirectory(tif, z_b_s);
                if(bits_num == 16){
                    u_short *single_slice = new u_short[piece * piece];
                    for(u_int del_z = z_b_s - z_b_s; del_z <= z_b_e - z_b_s; ++del_z){
                        for(int i = 0; i < stripNum; ++i){
                            TIFFReadEncodedStrip(tif, i, &(single_slice[i * stripByteCounts]), stripByteCounts);
                        }
                        for(u_int del_y = y_b_s - y_b_s; del_y <= y_b_e - y_b_s; ++del_y){
                            for(u_int del_x = x_b_s - x_b_s; del_x <=x_b_e - x_b_s; ++ del_x){
                                ROIData16[(z_o_s + del_z) * (w * h) +  (y_o_s + del_y) * w + (x_o_s + del_x)] = single_slice[(y_b_s + del_y) * piece + (x_b_s + del_x)];
                            }
                        }
                        if(TIFFReadDirectory(tif)){
                            continue;   
                        }else{
                            break;
                        }
                    }
                    delete []single_slice;
                }else if(bits_num == 8){
                    u_char *single_slice = new u_char[piece * piece];
                    for(u_int del_z = z_b_s - z_b_s; del_z <= z_b_e - z_b_s; ++del_z){
                        for(int i = 0; i < stripNum; ++i){
                            TIFFReadEncodedStrip(tif, i, &(single_slice[i * stripByteCounts]), stripByteCounts);
                        }
                        for(u_int del_y = y_b_s - y_b_s; del_y <= y_b_e - y_b_s; ++del_y){
                            for(u_int del_x = x_b_s - x_b_s; del_x <=x_b_e - x_b_s; ++ del_x){
                                ROIData8[(z_o_s + del_z) * (w * h) +  (y_o_s + del_y) * w + (x_o_s + del_x)] = single_slice[(y_b_s + del_y) * piece + (x_b_s + del_x)];
                            }
                        }
                        if(TIFFReadDirectory(tif)){
                            continue;   
                        }else{
                            break;
                        }
                    }
                    delete []single_slice;
                }
                TIFFClose(tif);
                t_i ++;
            }            
        }
    }
    if(ROIData8 || ROIData16){
        loadImageFlag = true;
    }
    return true;
}

u_short * Mostd::GetImageData16()
{
    if(bits_num == 16){
        return ROIData16;
    }else if(bits_num == 8){
        return 0;
    }
}

u_char * Mostd::GetImageData8()
{
    if(bits_num == 8){
        return ROIData8;
    }else if(bits_num == 16){
        return 0;
    }
    
}

void Mostd::cvOnMouse( int event, int x, int y, int flags, void* param )
{
    
    Mostd *m = reinterpret_cast<Mostd *>(param);
    //stringstream ss;
    //double x1 = vtkMath::Random(1, 10000);
    //ss<<x1;
    //string xStr(ss.str());
    
    if(event == cv::EVENT_LBUTTONDOWN){ 
        u_int nextPage = m->curPage + 1;
        if(nextPage >= m->maxPage){
            nextPage = 0;
        }
        cout<<nextPage<<endl;
        if(m->bits_num == 16){
            cv::Mat imageMat(cv::Size(m->imageWidth, m->imageHeight), CV_16SC1, &(m->GetImageData16()[m->signleImagePixelCounts * nextPage]));
            cv::imshow(m->windowName, imageMat);
            m->curPage = nextPage;
        }else if(m->bits_num == 8){
            cv::Mat imageMat(cv::Size(m->imageWidth, m->imageHeight), CV_8UC1, &(m->GetImageData8()[m->signleImagePixelCounts * nextPage]));
            cv::imshow(m->windowName, imageMat);
            if(imageMat.data){
                cout<<"rwrwr"<<endl;
            }
            m->curPage = nextPage;
        }
        cout<<m->curPage<<endl;
    
    }
}


bool Mostd::showImages()
{
    cv::namedWindow(windowName, 0);
    cv::setMouseCallback(windowName, cvOnMouse, this);
    if(loadImageFlag){
        if(bits_num == 16){
            cv::Mat imageMat(cv::Size(imageWidth, imageHeight), CV_16SC1, ROIData16);
            cv::imshow(windowName, imageMat);
            curPage = 0;
            maxPage = z_end - z_beg + 1;
        }else if(bits_num == 8){
            cv::Mat imageMat(cv::Size(imageWidth, imageHeight), CV_8UC1, ROIData8);
            cv::imshow(windowName, imageMat);
            curPage = 0;
            maxPage = z_end - z_beg + 1;
        }
    }
    return true;
}

vector<float>& Mostd::GetResolution()
{
    resolution.push_back(x_res);
    resolution.push_back(y_res);
    resolution.push_back(z_res);
    return resolution;
}


