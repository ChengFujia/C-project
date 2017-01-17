#include "opencv2/highgui/highgui.hpp"
#include "opencv2/imgproc/imgproc.hpp"
#include <iostream>

using namespace std;
using namespace cv;

Mat img,templ,result;
int match_method;
int max_Trackbar = 5;

void MatchingMethod(int , void *)
{
	Mat img_display;
	img.copyTo(img_display);

	// create matrix(size) to store result 
	// as the rightest or downest is not suitable for our template.. too small
	int result_cols = img.cols - templ.cols + 1;
	int result_rows = img.rows - templ.rows + 1;
	result.create(result_cols,result_rows,CV_32FC1);
	
	// match 
	matchTemplate(img,templ,result,match_method);
	normalize(result,result,0,1,NORM_MINMAX,-1,Mat());	// without color..

	// find match loc
	double minVal,maxVal;
	Point minLoc,maxLoc;
	Point matchLoc;
	minMaxLoc(result,&minVal,&maxVal,&minLoc,&maxLoc,Mat());

	// store matchLoc -- distinct from algorithm
	if (match_method == CV_TM_SQDIFF || match_method == CV_TM_SQDIFF_NORMED)
		matchLoc = minLoc;
	else
		matchLoc = maxLoc;
	
	// store final result
	rectangle(img_display,matchLoc,Point(matchLoc.x+templ.cols,matchLoc.y+templ.rows),Scalar(0,0,255),2,8,0);
	rectangle(result,matchLoc,Point(matchLoc.x+templ.cols,matchLoc.y+templ.rows),Scalar(0,0,255),2,8,0);

	// show final result
	imshow("Source Image",img_display);
	imwrite("result.jpg",img_display);
	imshow("Result Window",result);
	return ;
}

int main(int argc,char **argv)
{
	img = imread("original.jpg");
	templ = imread("template.jpg");
	
	// create window
	namedWindow("Source Image",CV_WINDOW_AUTOSIZE);
	namedWindow("Result Window",CV_WINDOW_AUTOSIZE);

	// create trackbar
	createTrackbar("David..","Source Image",&match_method,max_Trackbar,MatchingMethod);
	MatchingMethod(0,0);
	
	int logo = waitKey(0);
	//int logo = waitKey(5000);
	return 0;
}
