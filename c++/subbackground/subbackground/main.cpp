// subbackground.cpp : 定义控制台应用程序的入口点。
//

#include "stdafx.h"
#include "subbackgroundor.h"

void test(cv::Mat_<double> &mat1){
    cv::Mat_<double> mat3(2, 2);
    mat1 = mat3;
    mat3<<1, 3, 4, 1;
}


int main()
{
    //string image_path = "G:\\sulei\\workplace\\vs\\subbackground\\subbackground\\";
    //string image_name = "2.tif";
    //string dst_image_name = "G:\\sulei\\workplace\\vs\\subbackground\\subbackground\\5.tif";
    //cv::Mat image = cv::imread(image_path+image_name, CV_LOAD_IMAGE_UNCHANGED);
    //if(image.data){
    //    Subbor s(image, 50, dst_image_name);
    //}
    vector<string> s;
    cout<<s.size()<<endl;
    cout<<s.empty()<<endl;
    s.push_back("ssss");
    s.push_back("eeee");
    cout<<s[1]<<endl;
    cin.get();
    
}



    //string image_path = "G:\\sulei\\workplace\\vs\\subbackground\\subbackground\\";
    //string image_name = "1-1.tif";
    //cv::Mat image1 = cv::imread(image_path+image_name, CV_LOAD_IMAGE_UNCHANGED);
    //cv::namedWindow("111");
    //cv::imshow("111", image1);
    //cv::Mat image2;
    //image1.convertTo(image2, CV_32F);
    //cv::namedWindow("222");
    //cv::imshow("222", image2);
    //cv::imwrite("1-2.tif", image2);
    //cv::waitKey();
    
    //string image_path = "G:\\sulei\\workplace\\vs\\subbackground\\subbackground\\";
    //string image_name = "1-1.tif";
    //vector<string> v1;
    //v1.push_back(image_path + image_name);
    //Subbor s(v1, 3);
    //cin.get();