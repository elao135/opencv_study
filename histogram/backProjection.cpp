#include "opencv2/imgproc.hpp"
#include "opencv2/imgcodecs.hpp"
#include "opencv2/highgui.hpp"
#include <iostream>
#define TEST_IMAGE1 "/Users/minsu/Desktop/대학생 자료/2학년/robotics 인턴/opencv_ws/opencv_ws/black.jpeg"
#define TEST_IMAGE2 "/Users/minsu/Desktop/대학생 자료/2학년/robotics 인턴/opencv_ws/opencv_ws/white.jpeg"
#define LENNA_IMAGE "/Users/minsu/Desktop/대학생 자료/2학년/robotics 인턴/opencv_ws/opencv_ws/Lenna.png"
#define NASA "/Users/minsu/Desktop/대학생 자료/2학년/robotics 인턴/opencv_ws/opencv_ws/test.jpeg"
#define ASIAN "/Users/minsu/Desktop/대학생 자료/2학년/robotics 인턴/opencv_ws/opencv_ws/황인.jpeg"
using namespace cv;
using namespace std;
Mat src, hsv, mask;

int low = 20, up = 20;
const char* window_image = "Source image";

Point p1(0, 0);
Point p2(0, 0);

/// Function Headers
void Hist_and_Backproj( );

void showNewImg();

void onMouse(int event, int x, int y, int flags, void * param)
{
    switch (event)
    {
        case EVENT_LBUTTONDOWN :
            p1.x = x;
            p1.y = y;
            p2.x = x;
            p2.y = y;
            break;
        case EVENT_LBUTTONUP :
            p2.x = x;
            p2.y = y;
            showNewImg();
            
        default:
            break;
    }
}

void showNewImg()
{
    int wdth = p2.x - p1.x;
    int hgt = p2.y - p1.y;
    Rect roi(p1.x, p1.y, wdth, hgt);
    Mat draggedImage = src.clone();
    mask = draggedImage(roi);
    imshow("mask",mask);
    
    cvtColor(mask,mask,COLOR_BGR2HSV);
    
    Hist_and_Backproj();
}

/**
 * @function main
 */
int main( int, char** argv )
{
    /// Read the image
    src = imread(NASA);

    /// Transform it to HSV
    cvtColor( src, hsv, COLOR_BGR2HSV );

    /// Show the image
    namedWindow( window_image );
    imshow( window_image, src );

    setMouseCallback( window_image, onMouse, 0 );

    waitKey();
    return 0;
}

void Hist_and_Backproj( )
{
    Mat hist;
    int h_bins = 180; int s_bins = 255;
    int histSize[] = { h_bins, s_bins };

    float h_range[] = { 0, 180 };
    float s_range[] = { 0, 256 };
    const float* ranges[] = { h_range, s_range };

    int channels[] = { 0, 1 };

    calcHist( &mask, 1, channels, Mat(), hist, 2, histSize, ranges);

    normalize( hist, hist, 0, 255, NORM_MINMAX, -1, Mat());
    

    Mat backproj;
    calcBackProject( &hsv, 1, channels, hist, backproj, ranges, 1);

    imshow( "BackProj", backproj );
}
