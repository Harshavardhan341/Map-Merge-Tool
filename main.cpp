#include <string>
#include <iostream>
#include <algorithm>
#include <opencv2/opencv.hpp>
#include <opencv2/core.hpp>
#include <opencv2/core.hpp>
#include "opencv2/highgui/highgui_c.h"
#include "mapmerge.h"
#include <cstdlib>
#include <unistd.h>
using namespace std;
using namespace cv;

int main(int argc, char** argv)
{
  while(true){

    bool verbose = true;
    string outfile = "final.pgm";
    vector<string> infiles;
    float max_pairwise_distance = 5.0;
    float matches_threshold = 30.0;

    if(argc <= 3){
      cerr << "error: format <inputfile1> <inputfile2> <outputfile>" << endl;
      exit(-1);
    }
    
    infiles.push_back(argv[1]);
    infiles.push_back(argv[2]);
    outfile = argv[3];
   
    // load the images
    vector<Mat> images;
    for (size_t i = 0; i < infiles.size(); i++) {
      Mat image = imread(infiles[i].c_str(), 0); // 0=grayscale
      if (!image.data) {
        cerr << "error: image " << infiles[i] << " not loadable." << endl;
        exit(-1);
      }
      images.push_back(image);
    }

    // create the stitched map
    StitchedMap map(images[0],images[1], max_pairwise_distance, matches_threshold);
    // write to outfile if applicable
    if (outfile.size() != 0) {
      imwrite(outfile, map.get_stitch());
    }

    if (outfile.size() == 0 || verbose) { // generate some output
      cout << "rotation: "          << map.rotation << endl
          << "translation (x,y): " << map.transx << ", " << map.transy << endl
          << "matrix: "            << map.H << endl;
    }

    if (verbose) {
      namedWindow("wrap"); imshow("wrap", map.get_stitch()); imwrite("stitch.pgm", map.get_stitch());
      namedWindow("debug"); imshow("debug", map.get_debug()); imwrite("debug.pgm", map.get_debug());
      waitKey(5000);
      // while ((waitKey(0)&255) != 10) // RETURN
      //   ;
    }
    //usleep(10000000);
  }
  return 0;
}
