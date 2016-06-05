#include "preprocessor.h"

ParaOfPre::ParaOfPre():
tar_src(""), tar_dst(""), tar_file_pre(""), tar_file_post(""), mon_src(""), mon_dst(""), pro_src(""), pro_dst(""), crop_src(""), crop_dst(""), res_src(""), res_dst(""), 
mon_in_pre(""), mon_in_post(""), mon_out_pre(""), mon_out_post(""), sys_del("\\"), crop_in_pre(""), crop_in_post(""), crop_out_pre(""), crop_out_post(""),
x_beg(0), x_end(0), y_beg(0), y_end(0), block_width(0), block_height(0), pro_thick(0), process_num(0), serial_beg(0), serial_end(0), serial_bits(5), image_depth(0), 
crop_x(0), crop_y(0), crop_w(0), crop_h(0), res_in_pre(""), res_in_post(""), res_out_pre(""), res_out_post(""), res_fx(1), res_fy(1),
pro_in_pre(""), pro_in_post(""), pro_out_pre(""), pro_out_post("")
{
    
}

ParaOfPre::~ParaOfPre(){

}

Preprocessor::Preprocessor(int t, ParaOfPre p): pre_type(t), para(p){
    if(pre_type == 1){
        tar();
    }else if(pre_type == 2){
        montage();
    }else if(pre_type == 3){
        project();
    }else if(pre_type == 4){
        crop();
    }else if(pre_type == 5){
        resize();
    }
}

Preprocessor::~Preprocessor(){

}

int Preprocessor::montage(){
    string src = para.mon_src;
    string dst = para.mon_dst;
    string sys_del = para.sys_del;
    unsigned int serial_beg = para.serial_beg, serial_end = para.serial_end, 
                        x_beg = para.x_beg, x_end = para.x_end, 
                        y_beg = para.y_beg, y_end = para.y_end, 
                        block_width = para.block_width, block_height = para.block_height, serial_bits = para.serial_bits;
    unsigned int image_depth = para.image_depth;
    string image_pre = para.mon_in_pre, image_post = para.mon_in_post;
    string out_pre = para.mon_out_pre, out_post = para.mon_out_post; 
    #pragma omp parallel for num_threads(6) 
    for(int serial_num = int(serial_beg); serial_num <= int(serial_end); ++ serial_num){
        stringstream string_buffer;
        string serial_string("");
        cv::Mat out_image, block_image, re_block_image;
        cout<<serial_num<<": "<<omp_get_thread_num()<<endl;
        if(image_depth ==  16){
            out_image = cv::Mat((y_end - y_beg + 1) * block_height, (x_end - x_beg + 1) * block_width, CV_16UC1, cv::Scalar(0, 0, 0));
            //cout<<out_image.rows<<" "<<out_image.cols<<" "<<out_image.depth()<<endl;
            block_image = cv::Mat(block_height, block_width, CV_16UC1, cv::Scalar(0, 0, 0));
            re_block_image = cv::Mat(block_height, block_width, CV_16UC1, cv::Scalar(0, 0, 0));        
        }else{
            out_image = cv::Mat((y_end - y_beg + 1) * block_height, (x_end - x_beg + 1) * block_width, CV_8UC1, cv::Scalar(0, 0, 0));
            //cout<<out_image.rows<<" "<<out_image.cols<<" "<<out_image.depth()<<endl;
            block_image = cv::Mat(block_height, block_width, CV_8UC1, cv::Scalar(0, 0, 0));
            re_block_image = cv::Mat(block_height, block_width, CV_8UC1, cv::Scalar(0, 0, 0));    
        
        }
        string x_str, y_str, image_str, out_image_name;       
        string_buffer<<setw(serial_bits)<<setfill('0')<<serial_num;    
        string_buffer>>serial_string;
        string_buffer.clear();
        //cout<<serial_string<<endl;
        for(unsigned int x_in = x_beg; x_in <= x_end; ++ x_in){
            for(unsigned int y_in = y_beg; y_in <= y_end; ++ y_in){
                string_buffer<<setw(2)<<setfill('0')<<x_in;
                string_buffer>>x_str;
                string_buffer.clear();
                string_buffer<<setw(2)<<setfill('0')<<y_in;
                string_buffer>>y_str;
                string_buffer.clear();
                image_str = src + sys_del + serial_string + sys_del +image_pre + serial_string + "_" + x_str + "_" + y_str + image_post;
                block_image = cv::imread(image_str.c_str(), CV_LOAD_IMAGE_UNCHANGED);
                if(!block_image.data){
                    cout<<"----------------------"<<endl;
                    cout<<"Image Loaded Error!"<<endl;
                    cout<<image_str<<endl;
                    cout<<"----------------------"<<endl;
                    block_image = cv::Mat(block_height, block_width, CV_8UC1, cv::Scalar(0, 0, 0));
                }
                for(int y_block = 0; y_block < block_image.cols; ++ y_block){
                    block_image.col(y_block).copyTo(re_block_image.col(block_image.cols - y_block - 1));       
                }
                cv::Rect sub_roi((x_in - x_beg) * block_width, (y_in - y_beg) * block_height, block_width, block_height);                 
                cv::Mat sub_image(out_image, sub_roi);
                re_block_image.clone().copyTo(sub_image);
            }
                        
        }
        
        out_image_name = dst + sys_del + out_pre + serial_string + out_post;
        cout<<out_image_name<<endl;
        cv::imwrite(out_image_name, out_image);            
    }
    
    
    
    return 0;
} 

int Preprocessor::tar(){
    string src = para.tar_src;
    string dst = para.tar_dst;
    string tar_pre = para.tar_file_pre;
    string tar_post = para.tar_file_post;
    string serial_str(""), tar_file_path("");
    string sys_del = para.sys_del;
    unsigned int serial_beg = para.serial_beg, serial_end = para.serial_end, serial_bits = para.serial_bits;
#pragma omp parallel for num_threads(6) 
    for(int serial_num = int(serial_beg); serial_num <= int(serial_end); ++ serial_num){
        cout<<serial_num<<"  "<<omp_get_thread_num()<<endl;
        stringstream str_buffer;
        str_buffer<<setw(5)<<setfill('0')<<serial_num;
        str_buffer>>serial_str;
        str_buffer.clear();
        tar_file_path = src + sys_del + tar_pre + serial_str + tar_post;
        Tar tar1(tar_file_path);
        tar1.untar(dst);                
    }
    return 0;
}

int Preprocessor::crop(){
    string src = para.crop_src;
    string dst = para.crop_dst;
    unsigned int crop_x = para.crop_x;
    unsigned int crop_y = para.crop_y;
    unsigned int crop_w = para.crop_w;
    unsigned int crop_h = para.crop_h;
    unsigned int serial_beg = para.serial_beg;
    unsigned int serial_end = para.serial_end;
    string in_pre = para.crop_in_pre;
    string in_post = para.crop_in_post;
    string out_pre = para.crop_out_pre;
    string out_post = para.crop_out_post;
    unsigned int image_depth = para.image_depth;
    unsigned int serial_bits = para.serial_bits;
    string sys_del = para.sys_del;
    string serial_str(""), image_path(""), out_name(""), x_str(""), y_str(""), w_str(""), h_str("");
    stringstream str_buffer;
    str_buffer<<crop_x;
    str_buffer>>x_str;
    str_buffer.clear();
    str_buffer<<crop_y;
    str_buffer>>y_str;
    str_buffer.clear();
    str_buffer<<crop_w;
    str_buffer>>w_str;
    str_buffer.clear();   
    str_buffer<<crop_h;
    str_buffer>>h_str;
    str_buffer.clear();        
    cv::Mat out_image, in_image;
    cv::Rect roi(crop_x, crop_y, crop_w, crop_h);
    for(unsigned int serial_num(serial_beg); serial_num <= serial_end; ++ serial_num){
        str_buffer<<setw(5)<<setfill('0')<<serial_num;
        str_buffer>>serial_str;
        str_buffer.clear();
        cout<<serial_str<<endl;
        image_path = src + sys_del + in_pre + serial_str + in_post;
        in_image = cv::imread(image_path, CV_LOAD_IMAGE_UNCHANGED);
        if(!in_image.data){
            cout<<"Image Loaded Error!"<<endl;
            return -1;
        }
        if(crop_x <0 || crop_x + crop_w > in_image.size().width || crop_y < 0 || crop_y + crop_h > in_image.size().height){
            cout<<"Out of Range Error!"<<endl;
            return -1;
        }
        out_image = cv::Mat(in_image, roi);
        out_name = dst + sys_del + out_pre + serial_str + "_x_" + x_str + "_y_" + y_str + "_w_" + w_str + "_h_" +h_str + out_post;
        cout<<out_name;
        cv::imwrite(out_name, out_image);    
    
    }

    return 0;
}

int Preprocessor::resize(){
    string src = para.res_src;
    string dst = para.res_dst;
    string in_pre = para.res_in_pre;
    string in_post = para.res_in_post;
    string out_pre = para.res_out_pre;
    string out_post = para.res_out_post;
    unsigned int serial_beg = para.serial_beg;
    unsigned int serial_end = para.serial_end;
    double res_fx = para.res_fx;
    double res_fy = para.res_fy;
    string sys_del = para.sys_del;
#pragma omp parallel for num_threads(6) 
    for(int serial_num = serial_beg; serial_num <= int(serial_end); ++ serial_num){
        string serial_str(""), in_path(""), out_path("");
        stringstream str_buffer;
        cv::Mat in_image, out_image;
        str_buffer<<setw(5)<<setfill('0')<<serial_num;
        str_buffer>>serial_str;
        str_buffer.clear();
        cout<<serial_str<<endl;
        in_path = src + sys_del + in_pre + serial_str + in_post;
        cout<<in_path<<endl;
        out_path = dst + sys_del + out_pre + serial_str + out_post;
        in_image = cv::imread(in_path, CV_LOAD_IMAGE_UNCHANGED);
        cv::resize(in_image, out_image, cv::Size(), res_fx, res_fy, cv::INTER_LINEAR);
        cv::imwrite(out_path, out_image);
    }
    return 0;
}

int Preprocessor::project(){
    string src = para.pro_src, dst = para.pro_dst, in_pre = para.pro_in_pre, in_post = para.pro_in_post, out_pre = para.pro_out_pre, out_post = para.pro_out_post;
    string sys_del = para.sys_del;
    unsigned int thick_num = para.pro_thick, image_depth = para.image_depth, serial_beg = para.serial_beg, serial_end = para.serial_end, serial_bits = para.serial_bits;
    stringstream str_buffer;    
    string serial_str("");
    cv::Mat tmp_image, out_image;
    string this_image_name(""), out_image_name("");
    unsigned int pro_count = 0;
    for(unsigned int serial_num = serial_beg; serial_num <= serial_end; ++serial_num){
        str_buffer<<setw(5)<<setfill('0')<<serial_num;
        str_buffer>>serial_str;
        str_buffer.clear();
        cout<<serial_str;
        this_image_name = src + sys_del + in_pre + serial_str + in_post;
        out_image_name = dst + sys_del + out_pre + serial_str + out_post;
        tmp_image = cv::imread(this_image_name, CV_LOAD_IMAGE_UNCHANGED);
        if(pro_count == 0){
            if(image_depth == 8){
                out_image = cv::Mat(tmp_image.rows, tmp_image.cols, CV_8UC1, cv::Scalar(0, 0, 0));
            }else if(image_depth == 16){
                out_image = cv::Mat(tmp_image.rows, tmp_image.cols, CV_16UC1, cv::Scalar(0, 0, 0));
            }        
        }
        out_image = cv::max(out_image, tmp_image);
        ++ pro_count;
        if(pro_count == thick_num || serial_num == serial_end){
            cv::imwrite(out_image_name, out_image);
            pro_count = 0;    
        }
    }
    return 0;   
}




//#include "preprocessor.h"
//
//ParaOfPre::ParaOfPre():
//tar_src(""), tar_dst(""), tar_file_pre(""), tar_file_post(""), mon_src(""), mon_dst(""), pro_src(""), pro_dst(""), crop_src(""), crop_dst(""), res_src(""), res_dst(""), 
//mon_in_pre(""), mon_in_post(""), mon_out_pre(""), mon_out_post(""), sys_del("\\"), crop_in_pre(""), crop_in_post(""), crop_out_pre(""), crop_out_post(""),
//x_beg(0), x_end(0), y_beg(0), y_end(0), block_width(0), block_height(0), pro_thick(0), process_num(0), serial_beg(0), serial_end(0), serial_bits(5), image_depth(0), 
//crop_x(0), crop_y(0), crop_w(0), crop_h(0), res_in_pre(""), res_in_post(""), res_out_pre(""), res_out_post(""), res_fx(1), res_fy(1),
//pro_in_pre(""), pro_in_post(""), pro_out_pre(""), pro_out_post("")
//{
//    
//}
//
//ParaOfPre::~ParaOfPre(){
//
//}
//
//Preprocessor::Preprocessor(int t, ParaOfPre p): pre_type(t), para(p){
//    if(pre_type == 1){
//        tar();
//    }else if(pre_type == 2){
//        montage();
//    }else if(pre_type == 3){
//        project();
//    }else if(pre_type == 4){
//        crop();
//    }else if(pre_type == 5){
//        resize();
//    }
//}
//
//Preprocessor::~Preprocessor(){
//
//}
//
//int Preprocessor::montage(){
//    string src = para.mon_src;
//    string dst = para.mon_dst;
//    string sys_del = para.sys_del;
//    stringstream string_buffer;
//    unsigned int serial_beg = para.serial_beg, serial_end = para.serial_end, 
//                        x_beg = para.x_beg, x_end = para.x_end, 
//                        y_beg = para.y_beg, y_end = para.y_end, 
//                        block_width = para.block_width, block_height = para.block_height, serial_bits = para.serial_bits;
//    unsigned int image_depth = para.image_depth;
//    string image_pre = para.mon_in_pre, image_post = para.mon_in_post, serial_string("");
//    string out_pre = para.mon_out_pre, out_post = para.mon_out_post;
//    cv::Mat out_image, block_image, re_block_image;
//    if(image_depth ==  16){
//        out_image = cv::Mat((y_end - y_beg + 1) * block_height, (x_end - x_beg + 1) * block_width, CV_16UC1, cv::Scalar(0, 0, 0));
//        cout<<out_image.rows<<" "<<out_image.cols<<" "<<out_image.depth()<<endl;
//        block_image = cv::Mat(block_height, block_width, CV_16UC1, cv::Scalar(0, 0, 0));
//        re_block_image = cv::Mat(block_height, block_width, CV_16UC1, cv::Scalar(0, 0, 0));        
//    }else{
//        out_image = cv::Mat((y_end - y_beg + 1) * block_height, (x_end - x_beg + 1) * block_width, CV_8UC1, cv::Scalar(0, 0, 0));
//        cout<<out_image.rows<<" "<<out_image.cols<<" "<<out_image.depth()<<endl;
//        block_image = cv::Mat(block_height, block_width, CV_8UC1, cv::Scalar(0, 0, 0));
//        re_block_image = cv::Mat(block_height, block_width, CV_8UC1, cv::Scalar(0, 0, 0));    
//    
//    }
//    string x_str, y_str, image_str, out_image_name;    
//    for(unsigned int serial_num = serial_beg; serial_num <= serial_end; ++ serial_num){
//        string_buffer<<setw(serial_bits)<<setfill('0')<<serial_num;    
//        string_buffer>>serial_string;
//        string_buffer.clear();
//        cout<<serial_string<<endl;
//        for(unsigned int x_in = x_beg; x_in <= x_end; ++ x_in){
//            for(unsigned int y_in = y_beg; y_in <= y_end; ++ y_in){
//                string_buffer<<setw(2)<<setfill('0')<<x_in;
//                string_buffer>>x_str;
//                string_buffer.clear();
//                string_buffer<<setw(2)<<setfill('0')<<y_in;
//                string_buffer>>y_str;
//                string_buffer.clear();
//                image_str = src + sys_del + serial_string + sys_del +image_pre + serial_string + "_" + x_str + "_" + y_str + image_post;
//                block_image = cv::imread(image_str.c_str(), CV_LOAD_IMAGE_UNCHANGED);
//                if(!block_image.data){
//                    cout<<"Image Loaded Error!"<<endl;
//                    return -1;
//                }
//                for(int y_block = 0; y_block < block_image.cols; ++ y_block){
//                    block_image.col(y_block).copyTo(re_block_image.col(block_image.cols - y_block - 1));       
//                }
//                cv::Rect sub_roi((x_in - x_beg) * block_width, (y_in - y_beg) * block_height, block_width, block_height);                 
//                cv::Mat sub_image(out_image, sub_roi);
//                re_block_image.clone().copyTo(sub_image);
//            }
//                        
//        }
//        out_image_name = dst + sys_del + out_pre + serial_string + out_post;
//        cv::imwrite(out_image_name, out_image);            
//    }
//    return 0;
//} 
//
//int Preprocessor::tar(){
//    string src = para.tar_src;
//    string dst = para.tar_dst;
//    string tar_pre = para.tar_file_pre;
//    string tar_post = para.tar_file_post;
//    string serial_str(""), tar_file_path("");
//    string sys_del = para.sys_del;
//    unsigned int serial_beg = para.serial_beg, serial_end = para.serial_end, serial_bits = para.serial_bits;
//#pragma omp parallel for num_threads(6) 
//    for(int serial_num = int(serial_beg); serial_num <= int(serial_end); ++ serial_num){
//        cout<<serial_num<<"  "<<omp_get_thread_num()<<endl;
//        stringstream str_buffer;
//        str_buffer<<setw(5)<<setfill('0')<<serial_num;
//        str_buffer>>serial_str;
//        str_buffer.clear();
//        tar_file_path = src + sys_del + tar_pre + serial_str + tar_post;
//        Tar tar1(tar_file_path);
//        tar1.untar(dst);                
//    }
//    return 0;
//}
//
//int Preprocessor::crop(){
//    string src = para.crop_src;
//    string dst = para.crop_dst;
//    unsigned int crop_x = para.crop_x;
//    unsigned int crop_y = para.crop_y;
//    unsigned int crop_w = para.crop_w;
//    unsigned int crop_h = para.crop_h;
//    unsigned int serial_beg = para.serial_beg;
//    unsigned int serial_end = para.serial_end;
//    string in_pre = para.crop_in_pre;
//    string in_post = para.crop_in_post;
//    string out_pre = para.crop_out_pre;
//    string out_post = para.crop_out_post;
//    unsigned int image_depth = para.image_depth;
//    unsigned int serial_bits = para.serial_bits;
//    string sys_del = para.sys_del;
//    string serial_str(""), image_path(""), out_name(""), x_str(""), y_str(""), w_str(""), h_str("");
//    stringstream str_buffer;
//    str_buffer<<crop_x;
//    str_buffer>>x_str;
//    str_buffer.clear();
//    str_buffer<<crop_y;
//    str_buffer>>y_str;
//    str_buffer.clear();
//    str_buffer<<crop_w;
//    str_buffer>>w_str;
//    str_buffer.clear();   
//    str_buffer<<crop_h;
//    str_buffer>>h_str;
//    str_buffer.clear();        
//    cv::Mat out_image, in_image;
//    cv::Rect roi(crop_x, crop_y, crop_w, crop_h);
//    for(unsigned int serial_num(serial_beg); serial_num <= serial_end; ++ serial_num){
//        str_buffer<<setw(5)<<setfill('0')<<serial_num;
//        str_buffer>>serial_str;
//        str_buffer.clear();
//        cout<<serial_str<<endl;
//        image_path = src + sys_del + in_pre + serial_str + in_post;
//        in_image = cv::imread(image_path, CV_LOAD_IMAGE_UNCHANGED);
//        if(!in_image.data){
//            cout<<"Image Loaded Error!"<<endl;
//            return -1;
//        }
//        if(crop_x <0 || crop_x + crop_w > in_image.size().width || crop_y < 0 || crop_y + crop_h > in_image.size().height){
//            cout<<"Out of Range Error!"<<endl;
//            return -1;
//        }
//        out_image = cv::Mat(in_image, roi);
//        out_name = dst + sys_del + out_pre + serial_str + "_x_" + x_str + "_y_" + y_str + "_w_" + w_str + "_h_" +h_str + out_post;
//        cout<<out_name;
//        cv::imwrite(out_name, out_image);    
//    
//    }
//
//    return 0;
//}
//
//int Preprocessor::resize(){
//    string src = para.res_src;
//    string dst = para.res_dst;
//    string in_pre = para.res_in_pre;
//    string in_post = para.res_in_post;
//    string out_pre = para.res_out_pre;
//    string out_post = para.res_out_post;
//    unsigned int serial_beg = para.serial_beg;
//    unsigned int serial_end = para.serial_end;
//    double res_fx = para.res_fx;
//    double res_fy = para.res_fy;
//    string sys_del = para.sys_del;
//    string serial_str(""), in_path(""), out_path("");
//    unsigned int serial_num(0);
//    cv::Mat in_image, out_image;
//    stringstream str_buffer;
//    for(serial_num = serial_beg; serial_num <= serial_end; ++ serial_num){
//        str_buffer<<setw(5)<<setfill('0')<<serial_num;
//        str_buffer>>serial_str;
//        str_buffer.clear();
//        cout<<serial_str<<endl;
//        in_path = src + sys_del + in_pre + serial_str + in_post;
//        out_path = dst + sys_del + out_pre + serial_str + out_post;
//        in_image = cv::imread(in_path, CV_LOAD_IMAGE_UNCHANGED);
//        cv::resize(in_image, out_image, cv::Size(), res_fx, res_fy, cv::INTER_LINEAR);
//        cv::imwrite(out_path, out_image);
//    }
//    return 0;
//}
//
//int Preprocessor::project(){
//    string src = para.pro_src, dst = para.pro_dst, in_pre = para.pro_in_pre, in_post = para.pro_in_post, out_pre = para.pro_out_pre, out_post = para.pro_out_post;
//    string sys_del = para.sys_del;
//    unsigned int thick_num = para.pro_thick, image_depth = para.image_depth, serial_beg = para.serial_beg, serial_end = para.serial_end, serial_bits = para.serial_bits;
//    stringstream str_buffer;    
//    string serial_str("");
//    cv::Mat tmp_image, out_image;
//    string this_image_name(""), out_image_name("");
//    unsigned int pro_count = 0;
//    for(unsigned int serial_num = serial_beg; serial_num <= serial_end; ++serial_num){
//        str_buffer<<setw(5)<<setfill('0')<<serial_num;
//        str_buffer>>serial_str;
//        str_buffer.clear();
//        cout<<serial_str;
//        this_image_name = src + sys_del + in_pre + serial_str + in_post;
//        out_image_name = dst + sys_del + out_pre + serial_str + out_post;
//        tmp_image = cv::imread(this_image_name, CV_LOAD_IMAGE_UNCHANGED);
//        if(pro_count == 0){
//            if(image_depth == 8){
//                out_image = cv::Mat(tmp_image.rows, tmp_image.cols, CV_8UC1, cv::Scalar(0, 0, 0));
//            }else if(image_depth == 16){
//                out_image = cv::Mat(tmp_image.rows, tmp_image.cols, CV_16UC1, cv::Scalar(0, 0, 0));
//            }        
//        }
//        out_image = cv::max(out_image, tmp_image);
//        ++ pro_count;
//        if(pro_count == thick_num || serial_num == serial_end){
//            cv::imwrite(out_image_name, out_image);
//            pro_count = 0;    
//        }
//    }
//    return 0;   
//}