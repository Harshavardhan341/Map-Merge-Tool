#include <opencv2/opencv.hpp>
#include <iostream>

using namespace cv;

int main(){
    cv::Mat imMat(256,256, CV_8UC3);

    for(int y = 0 ; y < imMat.rows; y++){
        for(int x = 0 ; x < imMat.cols; x++){
            cv::Vec3b &p = imMat.at<cv::Vec3b>( y, x);
            p[0] = x;
            p[1] = y;
            p[2] = (int)((x+y)/2);
        }
    }
    imshow("openCVTest",imMat);
    waitKey(0);
    return 0;
}
