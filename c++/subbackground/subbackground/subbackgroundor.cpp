#include "subbackgroundor.h"

double round(double x){
    if(floor(x + 0.5) > floor(x)){
        return ceil(x);
    }else{
        return floor(x);
    }
}

Subbor::~Subbor(){
}

Subbor::Subbor(cv::Mat &image, int r, const string &dst_image_name): image_raw(image), doPresmooth(true){
    ball_radius = r;
    RollingBall ball(ball_radius);
    if(image.data){
        int image_type = image_raw.type();
        cv::Mat image_32f;
        cv::Mat image_back;
        cv::Mat image_subbed;
        image_raw.convertTo(image_32f, CV_32F);
        if(image_32f.data){
            rollingBallFloatBackground(image_32f, ball_radius, ball);
            if(image_type == 0){
                image_32f.convertTo(image_back, CV_8U);
            }else if(image_type == 2){
                image_32f.convertTo(image_back, CV_16U);
            }
            cv::subtract(image_raw, image_back, image_subbed);
            cv::imwrite(dst_image_name, image_subbed);
        }else{
            cout<<"Image error!"<<endl;
        }
    }
}

Subbor::Subbor(cv::Mat &image, int r): image_raw(image), doPresmooth(true){
    ball_radius = r;
    RollingBall ball(ball_radius);
    if(image.data){
        int image_type = image_raw.type();
        cv::Mat image_32f;
        cv::Mat image_back;
        cv::Mat image_subbed;
        image_raw.convertTo(image_32f, CV_32F);
        if(image_32f.data){
            rollingBallFloatBackground(image_32f, ball_radius, ball);
            if(image_type == 0){
                image_32f.convertTo(image_back, CV_8U);
            }else if(image_type == 2){
                image_32f.convertTo(image_back, CV_16U);
            }
            cv::subtract(image_raw, image_back, image_subbed);
            image_subbed.copyTo(image_raw);
        }else{
            cout<<"Image error!"<<endl;
        }
    }
}

bool Subbor::rollingBallFloatBackground(cv::Mat &image, double radius, RollingBall &ball){
    int image_type = image.type();
    float *pixels = reinterpret_cast<float *>(image.data);
    int width = image.cols;
    int height = image.rows;
    bool shrink = ball.shrinkFactor > 1;
    if(doPresmooth){
        filter3x3(image, MEAN);
    }
    double minmax[2];
    cv::minMaxIdx(image, &minmax[0], &minmax[1]);
    cv::Mat smallImage;
    if(shrink){
        shrinkImage(smallImage, image, ball.shrinkFactor);
    }else{
        smallImage = image;
    }
    rollBall(ball, smallImage);
    if(shrink){
        enlargeImage(smallImage, image, ball.shrinkFactor);
    }
    return true;
}


void Subbor::filter3x3(cv::Mat &image, int filter_type){
    int width = image.cols;
    int height = image.rows;
    float *pixels = reinterpret_cast<float *>(image.data);
    for(int y = 0;  y < height; ++y){
        filter3(pixels, width, y*width, 1, filter_type);
    }
    for(int x = 0;  x < width; ++x){
        filter3(pixels, height, x, width, filter_type);
    }
}

void Subbor::filter3(float *pixels, int length, int pixel0, int inc, int type){
    float v3 = pixels[pixel0];
    float v2 = v3;
    float v1;
    for(int i = 1, p = pixel0; i < length; ++i, p+=inc){
        v1 = v2;
        v2 = v3;
        if(i < length - 1){v3 = pixels[p + inc];}
        if(type == MAXIMUM){
            float max = v1 > v3? v1 : v3;
            if(v2 > max){max = v2;}
            pixels[p] = max;
        }else{
            pixels[p] = (v1 + v2 + v3) * 0.33333333f;
        }
    }
}

void Subbor::shrinkImage(cv::Mat &smallImage, cv::Mat &image, int shrinkFactor){
    int raw_type = image.type();
    int width = image.cols;
    int height = image.rows;
    float *pixels = reinterpret_cast<float*>(image.data);
    int sWidth = (width + shrinkFactor - 1) / shrinkFactor;
    int sHeight = (height + shrinkFactor - 1) / shrinkFactor;
    smallImage.create(sHeight, sWidth, CV_32F);
    float *sPixels = reinterpret_cast<float *>(smallImage.data);
    float min, thispixel;
    for(int ySmall = 0; ySmall < sHeight; ++ySmall){
        for(int xSmall = 0; xSmall < sWidth; ++xSmall){
            min = numeric_limits<float>::max();
            for(int j = 0, y = shrinkFactor * ySmall; j < shrinkFactor && y <height; ++j, ++y){
                for(int k = 0, x = shrinkFactor * xSmall; k < shrinkFactor && x < width; ++k, ++x){
                    thispixel = static_cast<float>(pixels[x + y * width]);
                    if(thispixel < min){
                        min = thispixel;
                    }
                }  
            }
            sPixels[xSmall + ySmall * sWidth] = min;
        }
    }
}

void Subbor::rollBall(RollingBall &ball, cv::Mat &smallImage){
    float *pixels = reinterpret_cast<float *>(smallImage.data);
    int width = smallImage.cols;
    int height = smallImage.rows;
    float *zBall = reinterpret_cast<float *>(ball.getBallData());
    int ballWidth = ball.width;
    int radius = ballWidth / 2;
    cv::Mat cacheMat(ballWidth, width, CV_32F);
    float *cache = reinterpret_cast<float *>(cacheMat.data);
    for(int y = -radius; y < height + radius; ++y){
        int nextLineToWriteInCache = (y + radius) % ballWidth;
        int nextLineToRead = y + radius;
        if(nextLineToRead < height){
            smallImage.row(nextLineToRead).copyTo(cacheMat.row(nextLineToWriteInCache));
            for(int x = 0, p = nextLineToRead * width; x < width; ++x, ++p){
                pixels[p] = -numeric_limits<float>::max();
            }            
        }
        int y0 = y - radius;
        if(y0 < 0){
            y0 = 0;
        }
        int yBall0 = y0 - y + radius;
        int yend = y + radius;
        if(yend >= height){
            yend = height - 1;   
        }
        for(int x = -radius; x < width + radius; ++x){
            float z = numeric_limits<float>::max();
            int x0 = x - radius;
            if(x0 < 0){
                x0 = 0;
            }
            int xBall0 = x0 - x + radius;
            int xend = x + radius;
            if(xend >= width){
                xend = width - 1;
            }
            for(int yp = y0, yBall = yBall0; yp <= yend; ++yp, ++yBall){
                int cachePointer = (yp % ballWidth) *width + x0;
                for(int xp = x0, bp = xBall0 + yBall * ballWidth; xp <= xend; ++xp, ++cachePointer, ++bp){
                    float zReduced = cache[cachePointer] - zBall[bp];
                    if(z > zReduced){
                        z = zReduced;
                    }
                }
            }
            for(int yp = y0, yBall = yBall0; yp <= yend; ++yp, ++yBall){
                for(int xp = x0, p = xp + yp *width, bp = xBall0 + yBall * ballWidth; xp < xend; ++xp, ++p, ++bp){
                    float zMin = z + zBall[bp];
                    if(pixels[p]< zMin){
                        pixels[p] = zMin;
                    }
                }
            }
        }
    }
}


void Subbor::enlargeImage(cv::Mat &smallImage, cv::Mat &image, int shrinkFactor){
    int width = image.cols;
    int height = image.rows;
    int smallWidth = smallImage.cols;
    int smallHeight = smallImage.rows;
    float *pixels = reinterpret_cast<float *>(image.data);
    float *sPixels = reinterpret_cast<float *>(smallImage.data);
    int *xSmallIndices = new int[width];
    float *xWeights = new float[width];
    makeInterpolationArrays(xSmallIndices, xWeights, width, smallWidth, shrinkFactor);
    int *ySmallIndices = new int[height];
    float *yWeights = new float[height];
    makeInterpolationArrays(ySmallIndices, yWeights, height, smallHeight, shrinkFactor);
    float *line0 = new float[width];
    float *line1 = new float[width];
    for(int x = 0; x < width; ++x){
        //cout<<x<<" "<<xWeights[x]<<" "<<sPixels[xSmallIndices[x]] <<" "<<sPixels[xSmallIndices[x] + 1]<<" "<<xSmallIndices[x] <<endl;
        line1[x] = sPixels[xSmallIndices[x]] * xWeights[x] + sPixels[xSmallIndices[x] + 1] * (1.0f - xWeights[x]);
    }
    int ySmallLine0 = -1;
    for(int y = 0; y < height; ++y){
        if(ySmallLine0 < ySmallIndices[y]){
            float *swap = line0;
            line0 = line1;
            line1 = swap;
            ySmallLine0++;
            int sYPointer = (ySmallIndices[y] + 1) * smallWidth;
            for(int x = 0; x < width; ++x){
                line1[x] = sPixels[sYPointer + xSmallIndices[x]] * xWeights[x] + sPixels[sYPointer + xSmallIndices[x] + 1] * (1.0f - xWeights[x]);
            }
        }
        float weight = yWeights[y];
        for(int x = 0, p = y * width; x < width; ++x, ++p){   
            pixels[p] = line0[x] * weight + line1[x] * (1.0f - weight);
        }
    }
}

void Subbor::makeInterpolationArrays(int *smallIndices, float *weights, int length, int smallLength, int shrinkFactor){
    for(int i = 0; i < length; ++i){
        int smallIndex = (i - shrinkFactor / 2) / shrinkFactor;
        if(smallIndex >= smallLength - 1){
            smallIndex = smallLength - 2;
        }
        smallIndices[i] = smallIndex;
        float distance = (i + 0.5f) / shrinkFactor - (smallIndex + 0.5f);
        weights[i] = 1.0f - distance;
    }
}


RollingBall::RollingBall(double radius){
    int arcTrimPer;
    if(radius <= 10){
        shrinkFactor = 1;
        arcTrimPer = 24;
    }else if(radius <= 30){
        shrinkFactor = 2;
        arcTrimPer = 24;
    }else if(radius <= 100){
        shrinkFactor = 4;
        arcTrimPer = 32;
    }else{
        shrinkFactor = 8;
        arcTrimPer = 40;
    }
    buildRollingBall(radius, arcTrimPer);
}

RollingBall::~RollingBall(){
}

void RollingBall::buildRollingBall(double &ballradius, int &arcTrimPer){
    double rsquare;
    int xtrim;
    int xval, yval;
    double smallballradius;
    int halfWidth;
    
    smallballradius = ballradius/shrinkFactor;
    if(smallballradius < 1){
        smallballradius = 1;
    }
    rsquare = smallballradius * smallballradius;
    xtrim = static_cast<int>(arcTrimPer * smallballradius / 100);
    halfWidth = static_cast<int>(cvRound(smallballradius - xtrim));
    width = 2 * halfWidth + 1;
    //data1 = MatrixXdrm(width, width);
    data2 = cv::Mat::Mat(width, width, CV_32FC1);
    float *q;
    for(int y = 0, p = 0; y < width; y++){
        q = data2.ptr<float>(y);
        for(int x = 0; x < width; x++, p++){
            xval = x - halfWidth;
            yval = y - halfWidth;
            double temp = rsquare - xval * xval - yval * yval;
            //data1(p) = data[p];
            q[x] = static_cast<float>(temp>0.0?(static_cast<double>(sqrt(temp))) : 0.0); 
        }
    }
}