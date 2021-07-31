#include "mapmerge.h"
#include "math.h"

StitchedMap::StitchedMap(Mat &img1, Mat &img2, float max_pairwise_distance, float matches_threshold)
{
  // load images, TODO: check that they're grayscale and Full Image Copy
  image1 = img1.clone();
  image2 = img2.clone();
  
  //print(image1);

  // create feature detector set.
  auto detector = cv::ORB::create();
  // Creating a DescriptionExtractor object
  Ptr<DescriptorExtractor> dexc = ORB::create();
  //BFMatcher dematc(NORM_HAMMING, false);
  BFMatcher dematc(NORM_HAMMING, true);

  // 1. extract keypoints
  detector->detect(image1, kpv1);
  detector->detect(image2, kpv2);

  // 2. extract descriptors
  dexc->compute(image1, kpv1, dscv1);
  dexc->compute(image2, kpv2, dscv2);

  // 3. match keypoints(Image of querying (querying) dscv2 for features similar to dscv1)
  dematc.match(dscv1, dscv2, matches);

  // 4. find matching point pairs with same distance in both images
  for (size_t i = 0; i < (int)matches.size(); i++) {

    /*
      The target image for finding feature points where query is the axis image 
      and train is similar to query. In this case, image1 is query and image2 is train.
    */
    KeyPoint a1 = kpv1[matches[i].queryIdx],
             b1 = kpv2[matches[i].trainIdx];
    
    /*
      Select feature points one by one in order, and if their Hamming distance 
      is more than matches_threshold, do the following. 
      Otherwise, return to the for loop without executing the following.
    */
    if (matches[i].distance > matches_threshold)
      continue;

    // Compare selected feature points with all feature points
    for (size_t j = 0; j < matches.size(); j++) {
      KeyPoint a2 = kpv1[matches[j].queryIdx],
               b2 = kpv2[matches[j].trainIdx];

      if (matches[j].distance > matches_threshold)
        continue;
      

      /*
        For each selected feature point, calculate the pairwise distance 
        to all feature points, and if it is greater than or equal to max_pairwise_distance 
        or zero, return to the inner for loop.
      */
      if ( fabs(norm(a1.pt-a2.pt) - norm(b1.pt-b2.pt)) > max_pairwise_distance ||
           fabs(norm(a1.pt-a2.pt) - norm(b1.pt-b2.pt)) == 0)
        continue;
      
      // Stores keypoint coordinates.
      coord1.push_back(a1.pt);
      coord1.push_back(a2.pt);
      coord2.push_back(b1.pt);
      coord2.push_back(b2.pt);
      
      // Store keypoints
      fil1.push_back(a1);
      fil1.push_back(a2);
      fil2.push_back(b1);
      fil2.push_back(b2);
    }
  }

  if (coord1.size() == 0)
    ;

  H = estimateAffine2D(coord2, coord1);
  
  /* 
    Affine transformation matrices H are of the form [a11 a12 b1; a21 a22 b2].
    The specific affine transformation is calculated by [x; y] = [a11 a12; a21 a22] * [X; Y] + [b1; b2].
  */
  // 6. calculate this stuff for information
  rotation = 180./M_PI*atan2(H.at<double>(0,1),H.at<double>(1,1)),
  transx   = H.at<double>(0,2),
  transy   = H.at<double>(1,2);
  scalex   = sqrt(pow(H.at<double>(0,0),2)+pow(H.at<double>(0,1),2));
  scaley   = sqrt(pow(H.at<double>(1,0),2)+pow(H.at<double>(1,1),2));
}

Mat StitchedMap::get_debug()
{
  Mat out;
  drawKeypoints(image1, kpv1, image1, Scalar(255,0,0));
  drawKeypoints(image2, kpv2, image2, Scalar(255,0,0));
  drawMatches(image1,fil1, image2,fil2, matches,out,Scalar::all(-1),Scalar::all(-1));
  return out;
}

// return the stitched maps
Mat StitchedMap::get_stitch()
{
  // create storage for new image and get transformations
  Mat image(image2.size(), image2.type());
  warpAffine(image2,image,H,image.size());

  // blend image1 onto the transformed image2
  // Reference : https://qiita.com/exp/items/5ecbda091c1d42aa1b20
  double alpha = 0.5;
  double beta  = 1.0 - alpha;
  double gamma = 0.0;
  addWeighted(image,alpha,image1,beta,gamma,image);

  return image;
}

StitchedMap::~StitchedMap() { }