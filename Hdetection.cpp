#include <stdio.h>
#include <iostream>
#include <stdlib.h>
#include <ctime>
#include "opencv2/core/core.hpp"
#include "opencv2/imgproc/imgproc.hpp"
//#include <opencv2/core/types.hpp>
//#include "opencv2/features2d/features2d.hpp"
#include "opencv2/highgui/highgui.hpp"
//#include <opencv2/opencv.hpp>
using namespace cv;
using namespace std;

float pi =22/7;
Mat img_rgb =   imread("H1.jpg",1);
int main()
{
  clock_t begin = clock();
	namedWindow( "win", WINDOW_NORMAL );
  namedWindow( "win4", WINDOW_NORMAL );
	//Mat img_rgb = imread("helipadH3.jpg",0);
	Mat img(img_rgb.rows,img_rgb.cols,CV_8UC3,Scalar(0,0,0));
	cvtColor(img_rgb,img,COLOR_BGR2HSV);
	//Mat img_rgb(img_rgb.rows,img_rgb.cols,CV_8UC1,Scalar(0));
	// cvtColor(img_hsv,img_rgb,CV_HSV2img_rgb);
	Mat canny_output(img_rgb.rows,img_rgb.cols,CV_8UC1,Scalar(0));
	Mat binary1(img_rgb.rows,img_rgb.cols,CV_8UC1,Scalar(0));
  Mat binary(img_rgb.rows,img_rgb.cols,CV_8UC1,Scalar(0));
  cout<<"a"<<endl;
	int thresh =255; 
	int threshhold = 245;
	vector<vector<Point> > contours;
  	vector<Vec4i> hierarchy;
  	//createTrackbar("thresh","win",&threshhold,255);
  	//while(1)
  	//{
  		// 
  int thresh1=69, thresh2=180, thresh3=05,thresh4=21,thresh5=27,thresh6=54;
  //adaptiveThreshold(img, binary, 200, ADAPTIVE_THRESH_GAUSSIAN_C, THRESH_BINARY, 3, 2);
  //{cannot found a way to use adaptive  threshholding for 6 parameters}
  for(int i=0;i<img.rows;i++)
    {
      for(int j=0;j<img.cols;j++) 
      {
        if(img.at<Vec3b>(i,j)[0]>=thresh1 && img.at<Vec3b>(i,j)[0]<=thresh2 && img.at<Vec3b>(i,j)[1]>=thresh3 && img.at<Vec3b>(i,j)[1]<=thresh4)  
          binary.at<uchar>(i,j)=255;
        else
          binary.at<uchar>(i,j)=0;
      }
    } 
  int erosion_size = 6;
  Mat element = getStructuringElement(cv::MORPH_CROSS,
              cv::Size(2 * erosion_size + 1, 2 * erosion_size + 1),
              cv::Point(erosion_size, erosion_size) );

  //dilate(binary1,binary,element);
  //dilate(binary1,binary,element);
  //dilate(binary1,binary,element);
  //dilate(binary1,binary,element);
  //erode(binary1,binary,element);
  //erode(binary1,binary,element);
  //erode(binary1,binary,element);
  //erode(binary1,binary,element);
  //erode(binary1,binary,element); 
    imshow("win4",binary);
  	//	namedWindow( "Contours1", WINDOW_AUTOSIZE );
  	//	imshow( "Contours1", binary );
  	//	waitKey(10);	
  	//}
  	
 //  	createTrackbar("thresh","win",&thresh,255);
	// while(1)
	// {
	 	Canny( binary, canny_output, thresh, thresh*3, 3 );
	 	//imshow("win1",canny_output);
	// 	waitKey(10);
	// }

  	findContours( canny_output, contours, hierarchy, RETR_CCOMP, CHAIN_APPROX_SIMPLE, Point(0, 0) );
  	Mat drawing = Mat::zeros( canny_output.size(), CV_8UC3 );
  	for( size_t i = 0; i< contours.size(); i++ )
    	{
       		// Scalar color = Scalar( rng.uniform(0, 255), rng.uniform(0,255), rng.uniform(0,255) );
        	drawContours( drawing, contours, (int)i, (0,0,255), 2, 8, hierarchy, 0, Point() );
     	}
    vector<vector<Point> > contours_poly( contours.size() );
    vector<Rect> boundRect( contours.size() );
    vector<Point2f>centers( contours.size() );
    vector<float>radius( contours.size() );
    for( size_t i = 0; i < contours.size(); i++ )
    {
        approxPolyDP( contours[i], contours_poly[i], 3, true );
        boundRect[i] = boundingRect( contours_poly[i] );
        minEnclosingCircle( contours_poly[i], centers[i], radius[i] );
    } 
    float Max=contourArea(contours[0]),secmax=contourArea(contours[0]),thrmax=contourArea(contours[0]),thrmaxi=0,Maxi=0,secmaxi=0;
    for  (unsigned int i = 0; i < contours.size(); i++)
    {
   		if((contourArea(contours[i])<Max)&&((contourArea(contours[i]))>secmax)&&((contourArea(contours[i]))>thrmax))
   		{
   			thrmax = secmax;
   			thrmaxi = secmaxi;
     		secmax = contourArea(contours[i]);
     		secmaxi = i;
		}
		if((contourArea(contours[i])<Max)&&((contourArea(contours[i]))<secmax)&&((contourArea(contours[i]))>thrmax))
		{
			thrmax = contourArea(contours[i]);
			thrmaxi = i;
		}
		if((contourArea(contours[i])>Max)&&((contourArea(contours[i]))>secmax))
   		{
   			thrmax = secmax;
   			thrmaxi = secmaxi;
   			secmax = Max;
   			secmaxi = Maxi;
   			Max = contourArea(contours[i]);
     		Maxi = i;
		}
   	}
   	cout<<contours.size()<<endl;
 //   	for (int i = 0; i < contours.size(); i++) 
 //   	{
 //    	Point coordinate_i_ofcontour = contours.size();
 //    	cout << endl << "contour with coordinates: x = " << coordinate_i_ofcontour.x << " y = " << coordinate_i_ofcontour.y;
	// }
   	Rect bounding_rect_Max;
   	Rect bounding_rect_secmax;
   	bounding_rect_Max = boundingRect(contours[Maxi]);
   	cout<<Maxi<<" "<<secmaxi<<"  "<<thrmax<<"  "<<thrmaxi<<"  "<<Max<<"  "<<secmax<<endl;
   	bounding_rect_secmax= boundingRect(contours[secmaxi]);
   	int Max_x,Max_y;
   	int secmax_x,secmax_y;
   	Max_x = bounding_rect_Max.x + bounding_rect_Max.width/2;
   	Max_y = bounding_rect_Max.y + bounding_rect_Max.height/2;
   	secmax_x = bounding_rect_secmax.x + bounding_rect_secmax.width/2;
   	secmax_y = bounding_rect_secmax.y + bounding_rect_secmax.height/2;
    if(abs((max_y - secmax_y) > 5 )|| abs((max_x - secmax_x) > 5 ) ||abs((max - secmax) > 5 ) )
    {
      cout<<"no H found/threshholding is not"<<endl;
    }
    else
    {

    cout<<Max_x<<"  "<<Max_y<<"  "<<secmax_x<<"  "<<secmax_y<<endl;
    vector<Moments> mu(contours.size() );
    for( int i = 0; i < contours.size(); i++ )
    { 
      mu[i] = moments( contours[i], false );
      //cout<<mc[i].x<<"  "<<mu[i].y<<endl; 
    }
     vector<Point2f> mc( contours.size() );
    //for( int i = 0; i < contours.size(); i++ )
    //{
      mc[thrmaxi] = Point2f( mu[thrmaxi].m10/mu[thrmaxi].m00 , mu[thrmaxi].m01/mu[thrmaxi].m00 );
      cout<<mc[thrmaxi].x<<"  "<<mc[thrmaxi].y<<endl; 
    //} 
    double a,b,c;
    a = mu[thrmaxi].m20/mu[thrmaxi].m00 - (mc[thrmaxi].x)*(mc[thrmaxi].x);
    b = 2*(mu[thrmaxi].m11/mu[thrmaxi].m00 - (mc[thrmaxi].x)*(mc[thrmaxi].y));
    c = mu[thrmaxi].m02/mu[thrmaxi].m00 - (mc[thrmaxi].y)*(mc[thrmaxi].y);

    //% Orientation (radians)
    double theta = 1/2*atan(b/(a-c)) + (a<c)*pi/2;
    cout<<theta*180/3.14<<endl; 
    namedWindow( "Contours", WINDOW_NORMAL );
    imshow( "Contours", drawing );
  //imshow("win",img_rgb);
    clock_t end = clock();
    double elapsed_secs = double(end-begin) / CLOCKS_PER_SEC ;
    cout<<elapsed_secs<<endl;
    }
	waitKey(0);
}
