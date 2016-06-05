#include "preprocessor.h"

int main(int argc, char *argv[])
{
    //QCoreApplication a(argc, argv);
    ParaOfPre para1;
    para1.res_dst = "W:\\lsu\\TDI11302020\\red\\resample";
    para1.res_src = "W:\\lsu\\TDI11302020\\red\\montage";
    para1.res_in_pre = "test_";
    para1.res_in_post = "_mon.tif";
    para1.res_out_pre = "test_";
    para1.res_out_post = "_res.tif";
    para1.res_fx = 0.03;
    para1.res_fy = 0.03;
    para1.serial_beg = 5;
    para1.serial_end = 4850;
    para1.serial_bits = 5;
    Preprocessor pre1(5, para1);
    cin.get();
    return 0;
}


    //ParaOfPre para1;
    //para1.res_dst = "G:\\sulei\\workplace\\vs\\preprocessor\\preprocessor\\dst\\res";
    //para1.res_src = "G:\\sulei\\workplace\\vs\\preprocessor\\preprocessor\\dst\\montage";
    //para1.res_in_pre = "test_";
    //para1.res_in_post = "_mon.tif";
    //para1.res_out_pre = "test_";
    //para1.res_out_post = "_res.tif";
    //para1.res_fx = 0.1;
    //para1.res_fy = 0.1;
    //para1.serial_beg = 3173;
    //para1.serial_end = 3178;
    //para1.serial_bits = 5;
    //Preprocessor pre1(5, para1);

    //ParaOfPre para1;
    //para1.tar_src = "G:\\sulei\\workplace\\vs\\preprocessor\\preprocessor\\src";
    //para1.tar_dst = "G:\\sulei\\workplace\\vs\\preprocessor\\preprocessor\\dst\\src";
    //para1.tar_file_pre = "";
    //para1.tar_file_post = ".tar";
    //para1.serial_beg = 2624;
    //para1.serial_end = 2624;
    //para1.serial_bits = 5;
    //Preprocessor pre1(1, para1);

    //ParaOfPre para1;  
    //para1.mon_src = "G:\\sulei\\workplace\\vs\\preprocessor\\preprocessor";
    //para1.mon_dst = "G:\\sulei\\workplace\\vs\\preprocessor\\preprocessor";
    //para1.serial_beg = 2624;
    //para1.serial_end  = 2624;
    //para1.x_beg = 40;
    //para1.x_end = 70;
    //para1.y_beg = 31;
    //para1.y_end = 69;
    //para1.block_width = 982;
    //para1.block_height = 1400;
    //para1.serial_bits = 5;
    //para1.image_depth = 16;
    //para1.mon_in_pre = "green__";
    //para1.mon_in_post = ".tif";
    //para1.mon_out_pre = "test_";
    //para1.mon_out_post = ".tif";
    //Preprocessor pre1(2, para1);
/*    Tar t("G:\\sulei\\workplace\\vs\\preprocessor\\preprocessor\\src\\02624.tar");
    t.untar("G:\\sulei\\workplace\\vs\\preprocessor\\preprocessor\\dst"); */   
    
    
    //ParaOfPre para1;  
    //para1.crop_dst = "G:\\sulei\\workplace\\vs\\preprocessor\\preprocessor\\dst\\crop";
    //para1.crop_src = "G:\\sulei\\workplace\\vs\\preprocessor\\preprocessor\\dst\\montage";
    //para1.crop_h = 1000;
    //para1.crop_w = 1000;
    //para1.crop_x =   6048;
    //para1.crop_y = 16448;
    //para1.crop_out_pre = "test_";
    //para1.crop_in_pre = "test_";
    //para1.crop_in_post = "_mon.tif";
    //para1.crop_out_post = ".tif";
    //para1.image_depth = 16;
    //para1.serial_beg = 3173;
    //para1.serial_end = 3178;
    //para1.serial_bits = 5;
    //Preprocessor pre1(4, para1);   