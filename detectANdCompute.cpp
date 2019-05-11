#include <stdio.h>
#include <iostream>
#include "opencv2/core/core.hpp"
#include "opencv2/features2d/features2d.hpp"
#include "opencv2/highgui/highgui.hpp"
#include <opencv2/opencv.hpp>
#include <opencv2/nonfree/xfeatures2d.hpp>
using namespace cv::xfeatures2d;
using namespace cv;
using namespace std;
//void readme();

/** @function main */
// class CV_EXPORTS DescriptorExtractor
// {
// public:
//     virtual ~DescriptorExtractor();

//     void compute( const Mat& image, vector<KeyPoint>& keypoints,
//                   Mat& descriptors ) const;
//     void compute( const vector<Mat>& images, vector<vector<KeyPoint> >& keypoints,
//                   vector<Mat>& descriptors ) const;

//     virtual void read( const FileNode& );
//     virtual void write( FileStorage& ) const;

//     virtual int descriptorSize() const = 0;
//     virtual int descriptorType() const = 0;

//     static Ptr<DescriptorExtractor> create( const string& descriptorExtractorType );

// protected:
//     ...
// };
int main()
{
  // if( argc != 3 )
  //  { return -1; }

  Mat img_1 = imread( "helipadH2", CV_LOAD_IMAGE_GRAYSCALE );
  Mat img_2 = imread( "helipadH3", CV_LOAD_IMAGE_GRAYSCALE );
  // Ptr<SURF> Surf = SURF::create();
  
  if( !img_1.data || !img_2.data )
   { return -1; }

  //-- Step 1: Detect the keypoints using SURF Detector
  int minHessian = 400;

  SurfFeatureDetector detector( minHessian );
  // Ptr<FastFeatureDetector> detector = FastFeatureDetector::create(277);
  std::vector<KeyPoint> keypoints_1, keypoints_2;

  detector.detect( img_1, keypoints_1 );
  detector.detect( img_2, keypoints_2 );

  //-- Step 2: Calculate descriptors (feature vectors)
  SurfDescriptorExtractor extractor;

  Mat descriptors_1, descriptors_2;

  extractor.compute( img_1, keypoints_1, descriptors_1 );
  extractor.compute( img_2, keypoints_2, descriptors_2 );

  //-- Step 3: Matching descriptor vectors with a brute force matcher
  BFMatcher matcher(NORM_L2);
  std::vector< DMatch > matches;
  matcher.match( descriptors_1, descriptors_2, matches );

  //-- Draw matches
  Mat img_matches;
  drawMatches( img_1, keypoints_1, img_2, keypoints_2, matches, img_matches );

  //-- Show detected matches
  imshow("Matches", img_matches );

  waitKey(0);

  return 0;
}

 /** @function readme */
 // void readme()
 // { std::cout << " Usage: ./SURF_descriptor <img1> <img2>" << std::endl; 