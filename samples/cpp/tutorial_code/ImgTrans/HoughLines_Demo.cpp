/**
 * @file HoughLines_Demo.cpp
 * @brief Demo code for Hough Transform
 * @author OpenCV team
 */

#include "opencv2/imgcodecs.hpp"
#include "opencv2/highgui.hpp"
#include "opencv2/imgproc.hpp"
#include <iostream>

using namespace cv;
using namespace std;

/// Global variables

/** General variables */
Mat src, edges;
Mat src_gray;
Mat probabilistic_hough;
int min_threshold = 0;
int max_trackbar = 150;
int canny_lowthreshold;

const char* probabilistic_name = "Probabilistic Hough Lines Demo";

int p_trackbar = max_trackbar;

/// Function Headers
void help();
void Probabilistic_Hough( int, void* );

/**
 * @function main
 */
int main( int, char** argv )
{
   /// Read the image
   src = imread( argv[1], IMREAD_COLOR );

   if( src.empty() )
     { help();
       return -1;
     }

   /// Pass the image to gray
   cvtColor( src, src_gray, COLOR_RGB2GRAY );

   canny_lowthreshold = 23;
   /// Apply Canny edge detector
   Canny( src_gray, edges, canny_lowthreshold, canny_lowthreshold * 3, 3 );

   /// Create Trackbars for Thresholds
   char thresh_label[100];
   sprintf( thresh_label, "Thres: %d + input", min_threshold );

   namedWindow( probabilistic_name, WINDOW_AUTOSIZE );
   createTrackbar( thresh_label, probabilistic_name, &p_trackbar, max_trackbar, Probabilistic_Hough);

   /// Initialize
   Probabilistic_Hough(0, 0);
   waitKey(0);
   return 0;
}

/**
 * @function help
 * @brief Indications of how to run this program and why is it for
 */
void help()
{
  printf("\t Hough Transform to detect lines \n ");
  printf("\t---------------------------------\n ");
  printf(" Usage: ./HoughLines_Demo <image_name> \n");
}

/**
 * @function Probabilistic_Hough
 */
void Probabilistic_Hough( int, void* )
{
  vector<Vec4i> p_lines;
  cvtColor( edges, probabilistic_hough, COLOR_GRAY2BGR );

  /// 2. Use Probabilistic Hough Transform
  HoughLinesP( edges, p_lines, 1, CV_PI/180, min_threshold + p_trackbar, 30, 10 );
//printf("threshold=%d\n",min_threshold + p_trackbar);

  /// Show the result
  for( size_t i = 0; i < p_lines.size(); i++ )
     {
       Vec4i l = p_lines[i];
       line( probabilistic_hough, Point(l[0], l[1]), Point(l[2], l[3]), Scalar(255,0,0), 3, LINE_AA);
printf("line[%d]=(%d,%d),(%d,%d)\n", (int)i,l[0], l[1], l[2], l[3] );
     }

   imshow( probabilistic_name, probabilistic_hough );
}
