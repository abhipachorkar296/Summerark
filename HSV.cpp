#include"opencv2/highgui/highgui.hpp"
#include"opencv2/imgproc/imgproc.hpp"
#include"opencv2/core/core.hpp"
using namespace cv;
using namespace std;
//VideoCapture vid(0);
Mat img1=imread("H2.jpg",1);
Mat img(img1.rows,img1.cols,CV_8UC3,Scalar(0,0,0));
Mat dum(img1.rows,img1.cols,CV_8UC1,Scalar(0));


int thresh1=165, thresh2=169, thresh3=04,thresh4=60,thresh5=166,thresh6=249;
// void (int t, void* param)
// {
	
	
// 	for(int i=0;i<img.rows;i++)
// 	{
// 		for(int j=0;j<img.cols;j++) 
// 		{
// 			if(img.at<Vec3b>(i,j)[0]>=thresh1 && img.at<Vec3b>(i,j)[0]<=thresh2 && img.at<Vec3b>(i,j)[1]>=thresh3 && img.at<Vec3b>(i,j)[1]<=thresh4)	
// 				dum.at<uchar>(i,j)=255;
// 			else
// 				dum.at<uchar>(i,j)=0;
// 		}
// 	}
// 	imshow("win",dum);
// }
int main()
{
	cvtColor(img1,img,COLOR_BGR2HSV);
	namedWindow("win",WINDOW_NORMAL);
	createTrackbar("Min Hue","win", &thresh1, 180 );	
	createTrackbar("High Hue","win", &thresh2, 180 );
	createTrackbar("Min Saturation","win", &thresh3, 255 );
	createTrackbar("High Saturation","win", &thresh4, 255 );
	createTrackbar("Min Value","win", &thresh5, 255 );
	createTrackbar("High Value","win", &thresh6, 255 );
	while(1)
	{
		for(int i=0;i<img.rows;i++)
		{
			for(int j=0;j<img.cols;j++) 
			{
				if(img.at<Vec3b>(i,j)[0]>=thresh1 && img.at<Vec3b>(i,j)[0]<=thresh2 && img.at<Vec3b>(i,j)[1]>=thresh3 && img.at<Vec3b>(i,j)[1]<=thresh4)	
					dum.at<uchar>(i,j)=255;
				else
					dum.at<uchar>(i,j)=0;
			}
		}	
		imshow("win",dum);
		waitKey(1);
	}

		
}