#include <math.h>
#include <Eigen/Dense>
#include <Eigen/Core>
#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <iostream>
#include <limits>
using namespace std;
//typedef Eigen::Matrix<double, Eigen::Dynamic, Eigen::Dynamic, Eigen::RowMajor> MatrixXdrm;
double round(double x);
class RollingBall;
#define MEAN 1
#define MAXIMUM 0

void TestImAdjust(cv::Mat &mat_in, int low_in, int high_in, int low_out, int hign_out);


class Subbor{
    int ball_radius;
    cv::Mat &image_raw;
    bool createBackground;
    bool doPresmooth;
    bool correctCorners;
    bool rollingBallFloatBackground(cv::Mat &image, double radius, RollingBall&ball);
    void filter3x3(cv::Mat &image, int filter_type);
    void filter3(float *pixels, int length, int pixel0, int inc, int type);
    void shrinkImage(cv::Mat &smallImage, cv::Mat &image, int shrinkFactor);
    void rollBall(RollingBall &ball, cv::Mat &smallImage);
    void enlargeImage(cv::Mat &smallImage, cv::Mat &image, int shrinkFactor);
    void makeInterpolationArrays(int *smallIndices, float *weight, int width, int smallWidth, int shrinkFactor);
public:
    Subbor(cv::Mat &image, int r, const string &dst_image_name);
    Subbor(cv::Mat &image, int r);
    ~Subbor();
};




class RollingBall{
public:
    RollingBall(double radius);
    ~RollingBall();
    uchar *getBallData(){return data2.data;}
    cv::Mat &getBallMat(){return data2;}
    int shrinkFactor;
    int width;
    
private:
    void buildRollingBall(double &ballradius, int &arcTrimPer);
    //MatrixXdrm data1;
    cv::Mat data2;
};