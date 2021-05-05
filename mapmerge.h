#ifndef MAPMERGE_H
#define MAPMERGE_H

#include <iostream>
#include <stdio.h>
#include <math.h>
#include <vector>
#include <opencv2/opencv.hpp>
#include <opencv2/core.hpp>
#include <opencv2/core.hpp>

using namespace cv;
using namespace std;

class StitchedMap
{
public:
  StitchedMap(Mat &im1, Mat &im2, float max_distance=5.);
  ~StitchedMap();

  cv::Mat get_debug();
  cv::Mat get_stitch();

  cv::Mat H; // transformation matrix
  cv::Mat image1, image2,
      dscv1, dscv2;

  vector<KeyPoint> kpv1,kpv2;
  vector<KeyPoint> fil1,fil2;
  vector<Point2f>  coord1,coord2;
  vector<DMatch>   matches;

  double rotation,transx,transy,scalex,scaley;
};

#endif // MAPMERGE_H
