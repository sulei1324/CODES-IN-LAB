#include "Worker.h"

ParaOfPre::ParaOfPre():
tar_src(""), tar_dst(""), tar_file_pre(""), tar_file_post(""), mon_src(""), mon_dst(""), pro_src(""), pro_dst(""), crop_src(""), crop_dst(""), res_src(""), res_dst(""), 
mon_in_pre(""), mon_in_post(""), mon_out_pre("test_"), mon_out_post("_mon.tif"), sys_del("\\"), crop_in_pre(""), crop_in_post(""), crop_out_pre("test_"), crop_out_post("_crop.tif"),
x_beg(0), x_end(0), y_beg(0), y_end(0), block_width(0), block_height(0), pro_thick(0), process_num(0), serial_beg(0), serial_end(0), serial_bits(5), image_depth(0), 
crop_x(0), crop_y(0), crop_w(0), crop_h(0), res_in_pre(""), res_in_post(""), res_out_pre("test_"), res_out_post("_res.tif"), res_fx(1), res_fy(1),
pro_in_pre(""), pro_in_post(""), pro_out_pre("test_"), pro_out_post("_pro.tif"), thread_num(4), auto_src(""), auto_dst("")
{
    
}

ParaOfPre::~ParaOfPre(){

}

Preprocessor::Preprocessor(int t, ParaOfPre p): pre_type(t), para(p){

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
                        block_width = para.block_width, block_height = para.block_height, serial_bits = para.serial_bits,
                        thread_num = para.thread_num;
    unsigned int image_depth = para.image_depth;
    string image_pre = para.mon_in_pre, image_post = para.mon_in_post;
    string out_pre = para.mon_out_pre, out_post = para.mon_out_post; 
#pragma omp parallel for num_threads(thread_num) 
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
                    if(image_depth == 8){
                        block_image = cv::Mat::zeros(block_height, block_width, CV_8UC1);
                    }else if(image_depth == 16){
                        block_image = cv::Mat::zeros(block_height, block_width, CV_16UC1);
                    }
                    
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
    unsigned int serial_beg = para.serial_beg, serial_end = para.serial_end, serial_bits = para.serial_bits, thread_num = para.thread_num;
#pragma omp parallel for num_threads(thread_num) 
    for(int serial_num = int(serial_beg); serial_num <= int(serial_end); ++ serial_num){
        cout<<serial_num<<"  "<<omp_get_thread_num()<<endl;
        stringstream str_buffer;
        str_buffer<<setw(serial_bits)<<setfill('0')<<serial_num;
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
    unsigned int thread_num = para.thread_num;
    string in_pre = para.crop_in_pre;
    string in_post = para.crop_in_post;
    string out_pre = para.crop_out_pre;
    string out_post = para.crop_out_post;
    unsigned int image_depth = para.image_depth;
    unsigned int serial_bits = para.serial_bits;
    string sys_del = para.sys_del;
    string x_str(""), y_str(""), w_str(""), h_str("");
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
    cv::Rect roi(crop_x, crop_y, crop_w, crop_h);
#pragma omp parallel for num_threads(thread_num) 
    for(int serial_num = int(serial_beg); serial_num <= int(serial_end); ++ serial_num){
        cv::Mat out_image, in_image;
        stringstream tmp_strBuffer;
        string serial_str, out_name, image_path;
        tmp_strBuffer<<setw(serial_bits)<<setfill('0')<<serial_num;
        tmp_strBuffer>>serial_str;
        tmp_strBuffer.clear();
        cout<<serial_str<<" "<<omp_get_thread_num()<<endl;
        image_path = src + sys_del + in_pre + serial_str + in_post;
        in_image = cv::imread(image_path, CV_LOAD_IMAGE_UNCHANGED);
        if(!in_image.data){
            cout<<image_path<<" Loaded Error!"<<endl;
            continue;
        }
        if(crop_x < 0 || crop_x + crop_w > in_image.size().width || crop_y < 0 || crop_y + crop_h > in_image.size().height){
            cout<<"Out of Range Error!"<<endl;
            continue;
        }
        out_image = cv::Mat(in_image, roi);
        out_name = dst + sys_del + out_pre + serial_str + "_x" + x_str + "_y" + y_str + "_w" + w_str + "_h" +h_str + out_post;
        cout<<out_name<<endl;
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
    unsigned int serial_end = para.serial_end, serial_bits = para.serial_bits, thread_num = para.thread_num;
    double res_fx = para.res_fx;
    double res_fy = para.res_fy;
    string sys_del = para.sys_del;
#pragma omp parallel for num_threads(thread_num) 
    for(int serial_num = serial_beg; serial_num <= int(serial_end); ++ serial_num){
        string serial_str(""), in_path(""), out_path("");
        stringstream str_buffer;
        cv::Mat in_image, out_image;
        str_buffer<<setw(serial_bits)<<setfill('0')<<serial_num;
        str_buffer>>serial_str;
        str_buffer.clear();
        cout<<serial_str<<endl;
        in_path = src + sys_del + in_pre + serial_str + in_post;
        //cout<<in_path<<endl;
        out_path = dst + sys_del + out_pre + serial_str + out_post;
        //cout<<in_path<<endl;
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
        str_buffer<<setw(serial_bits)<<setfill('0')<<serial_num;
        str_buffer>>serial_str;
        str_buffer.clear();
        cout<<serial_str<<endl;
        this_image_name = src + sys_del + in_pre + serial_str + in_post;
        out_image_name = dst + sys_del + out_pre + serial_str + out_post;
        tmp_image = cv::imread(this_image_name, CV_LOAD_IMAGE_UNCHANGED);
        if(pro_count == 0){
            if(image_depth == 8){
                out_image = cv::Mat::zeros(tmp_image.rows, tmp_image.cols, CV_8UC1);
            }else if(image_depth == 16){
                out_image = cv::Mat::zeros(tmp_image.rows, tmp_image.cols, CV_16UC1);
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

void Preprocessor::run()
{
    cout<<"Work begins!"<<endl;
    if(pre_type == 1){
        tar();
    }else if(pre_type == 2){
        montage();
    }else if(pre_type == 3){
        groupProject();
    }else if(pre_type == 4){
        resize();
    }else if(pre_type == 5){
        crop();
    }else if(pre_type == 6){
        autoWork();
    }
    cout<<"Work Has Been Done!"<<endl;
}

int Preprocessor::autoWork()
{
    buildWorkGroup();
    int groupNum = static_cast<int>(workPool.size());
    string tarSrc = para.auto_src, autoDst = para.auto_dst, sysDel = para.sys_del,
             tarDst = autoDst +  sysDel + "src", monSrc = tarDst, monDst = autoDst + sysDel + "montage",
             proSrc = monDst, proDst = autoDst + sysDel + "project", resSrc = monDst, resDst = autoDst + sysDel + "resize",
             tarPre = para.tar_file_pre, tarPost = para.tar_file_post, monInPre = para.mon_in_pre, monInPost = para.mon_in_post;
    u_int xBeg = para.x_beg, xEnd = para.x_end, yBeg = para.y_beg, yEnd = para.y_end, blockWidth = para.block_width, blockHeight = para.block_height;
    u_int monWidth = blockWidth * (xEnd - xBeg + 1);
    u_int monHeght = blockHeight * (yEnd - yBeg + 1);
    if(_access(autoDst.c_str(), 0) == -1){
        _mkdir(autoDst.c_str());
        _mkdir(tarDst.c_str());
        _mkdir(monDst.c_str());
        _mkdir(proDst.c_str());
        _mkdir(resDst.c_str());
    }else{
        if(_access(tarDst.c_str(), 0) == -1){
            _mkdir(tarDst.c_str());
        }
        if(_access(monDst.c_str(), 0) == -1){
            _mkdir(monDst.c_str());
        }
        if(_access(proDst.c_str(), 0) == -1){
            _mkdir(proDst.c_str());
        }
        if(_access(resDst.c_str(), 0) == -1){
            _mkdir(resDst.c_str());
        }
    }
#pragma omp parallel for num_threads(para.thread_num)
    for(int i = 0; i < groupNum; ++i){
        vector<unsigned int> &tmpGroup = workPool.at(i);
        int groupSize = static_cast<int>(tmpGroup.size());
        u_int proIndex = 1;
        string startSerial, endSerial;
        for(int j = 0; j < groupSize; ++j){
            if(proIndex > para.pro_thick){
                proIndex = 1;
            }
            string tmpSerial;
            stringstream tmpStream;   
            tmpStream<<setw(5)<<setfill('0')<<tmpGroup.at(j);
            tmpStream>>tmpSerial;
            tmpStream.clear();
            cv::Mat inImage, proImage, resImage, monImage, blockImage, inverseRowBlockImage;
            if(para.image_depth == 8){
                monImage = cv::Mat::zeros(monHeght, monWidth, CV_8UC1);
                inverseRowBlockImage = cv::Mat::zeros(blockHeight, blockWidth, CV_8UC1);
            }else if(para.image_depth == 16){
                monImage = cv::Mat::zeros(monHeght, monWidth, CV_16UC1);
                inverseRowBlockImage = cv::Mat::zeros(blockHeight, blockWidth, CV_16UC1);
            }
            if(proIndex == 1){
                startSerial = tmpSerial;
                if(para.image_depth == 8){
                    proImage = cv::Mat::zeros(monHeght, monWidth, CV_8UC1);
                }else if(para.image_depth == 16){
                    proImage = cv::Mat::zeros(monHeght, monWidth, CV_16UC1);
                }
            }
            
            string tarName = tarSrc + sysDel + tarPre + tmpSerial + tarPost;
            Tar tmpTar(tarName);
            bool tarFlag = tmpTar.untar(tarDst);
            if(tarFlag){
                cout<<tarName<<" "<<omp_get_thread_num()<<endl;
                for(u_int x = xBeg; x <= xEnd; ++x){
                    for(u_int y = yBeg; y <= yEnd; ++y){
                        string monInName;
                        tmpStream<<monSrc<<sysDel<<tmpSerial<<sysDel<<monInPre<<tmpSerial<<"_"<<setw(2)<<setfill('0')<<x<<"_"<<setw(2)<<setfill('0')<<y<<monInPost;
                        tmpStream>>monInName;
                        tmpStream.clear();
                        blockImage = cv::imread(monInName, CV_LOAD_IMAGE_UNCHANGED);
                        if(!blockImage.data){
                            cout<<"----------------------"<<endl;
                            cout<<"Image Loaded Error!"<<endl;
                            cout<<monInName<<endl;
                            cout<<"----------------------"<<endl;
                            if(para.image_depth == 8){
                                blockImage = cv::Mat::zeros(blockHeight, blockWidth, CV_8UC1);
                            }else if(para.image_depth == 16){
                                blockImage = cv::Mat::zeros(blockHeight, blockWidth, CV_16UC1);
                            }
                        }
                        for(int col = 0; col < blockImage.cols; ++col){
                            blockImage.col(col).copyTo(inverseRowBlockImage.col(blockImage.cols - col - 1));
                        }
                        cv::Rect blockRoi((x - xBeg) * blockWidth, (y - yBeg) * blockHeight, blockWidth, blockHeight);
                        inverseRowBlockImage.copyTo(monImage(blockRoi));
                    }  
                }
                string monOutName = monDst + sysDel + para.mon_out_pre + tmpSerial + para.mon_out_post;
                string resOutName = resDst + sysDel + para.res_out_pre + tmpSerial + para.res_out_post;
                cv::imwrite(monOutName, monImage);
                cout<<monOutName<<" "<<omp_get_thread_num()<<endl;
                cv::resize(monImage, resImage, cv::Size(), para.res_fx, para.res_fy, cv::INTER_AREA);
                cv::imwrite(resOutName, resImage);
                cout<<resOutName<<" "<<omp_get_thread_num()<<endl;
                proImage = cv::max(monImage, proImage);
                if(proIndex == para.pro_thick || j == groupSize - 1){
                    endSerial = tmpSerial;
                    string proOutName = proDst + sysDel + para.pro_out_pre + startSerial + "-" + endSerial + para.pro_out_post;
                    cv::imwrite(proOutName, proImage);
                    cout<<proOutName<<" "<<omp_get_thread_num()<<endl;
                }
                
            }else{
                cout<<"Tar Error!"<<endl;
            }
            ++proIndex;
        }
    }
    return 0;
}

int Preprocessor::buildWorkGroup()
{
    u_int sBeg = para.serial_beg;
    u_int sEnd = para.serial_end;
    u_int threadNum = para.thread_num;
    u_int proThick = para.pro_thick;
    u_int threadIndex = 0;
    vector<vector<unsigned int>> tmpPool(threadNum);
    for(u_int i = sBeg; i <= sEnd; ){
        if(threadIndex == threadNum){
            threadIndex = 0;
        }
        u_int workSerial = 0;
        for(u_int j = 0; j < proThick; ++j){
            workSerial = i + j;
            if(workSerial > sEnd){
                break;
            }
            tmpPool.at(threadIndex).push_back(workSerial);
        }
        i = workSerial + 1;
        ++threadIndex;
    }
    workPool = tmpPool;
    cout<<workPool.size()<<endl;
    for(u_int i = 0; i < workPool.size(); ++i){
        cout<<"thread: "<<i<<endl;
        for(u_int j = 0; j < workPool.at(i).size(); ++j){
            cout<<workPool.at(i).at(j)<<endl;
        }
        cout<<"--------------"<<endl;
    }
    return 0;
}

int Preprocessor::groupProject()
{
    buildWorkGroup();
    u_int threadNum = para.thread_num;
    u_int groupNum = workPool.size();
    string srcFile = para.pro_src, dstFile = para.pro_dst, imagePre = para.pro_in_pre, sysDel = para.sys_del,
             imagePost = para.pro_in_post, outPre = para.pro_out_pre, outPost = para.pro_out_post;
#pragma omp parallel for num_threads(threadNum)
    for(int i = 0; i < static_cast<int>(groupNum); ++i){
        vector<unsigned int> &tmpGroup = workPool.at(i);
        int groupSize = static_cast<int>(tmpGroup.size());
        cv::Mat inImage, outImage;
        u_int proIndex = 1;
        string startSerial, endSerial;
        for(int j = 0; j < groupSize; ++j){
            if(proIndex > para.pro_thick){
                proIndex = 1;
            }
            stringstream tmpStream;
            string tmpSerial, inName, outName;
            tmpStream<<setw(5)<<setfill('0')<<(tmpGroup.at(j));
            tmpStream>>tmpSerial;
            tmpStream.clear();
            inName = srcFile + sysDel + imagePre + tmpSerial + imagePost;
            cout<<inName<<" "<<omp_get_thread_num()<<endl;
            inImage = cv::imread(inName, CV_LOAD_IMAGE_UNCHANGED);
            if(proIndex == 1){
                startSerial = tmpSerial;
                if(para.image_depth == 8){
                    outImage = cv::Mat::zeros(inImage.rows, inImage.cols, CV_8UC1);
                }else if(para.image_depth == 16){
                    outImage = cv::Mat::zeros(inImage.rows, inImage.cols, CV_16UC1);
                }
            }
            outImage = cv::max(inImage, outImage);
            if(proIndex == para.pro_thick || j == groupSize - 1){
                endSerial = tmpSerial;
                outName = dstFile + sysDel + outPre + startSerial + "-" + endSerial + outPost;
                cv::imwrite(outName, outImage);
            }
            ++proIndex;
        }   
    }
    return 0;
}
