#include "opencv2/imgproc.hpp"
#include "opencv2/imgcodecs.hpp"
#include "opencv2/highgui.hpp"
#include <iostream>
#define TEST_IMAGE1 "/Users/minsu/Desktop/대학생 자료/2학년/robotics 인턴/opencv_ws/opencv_ws/black.jpeg"
#define TEST_IMAGE2 "/Users/minsu/Desktop/대학생 자료/2학년/robotics 인턴/opencv_ws/opencv_ws/white.jpeg"
#define LENNA_IMAGE "/Users/minsu/Desktop/대학생 자료/2학년/robotics 인턴/opencv_ws/opencv_ws/Lenna.png"
#define NASA "/Users/minsu/Desktop/대학생 자료/2학년/robotics 인턴/opencv_ws/opencv_ws/test.jpeg"
#define SKIN "/Users/minsu/Desktop/대학생 자료/2학년/robotics 인턴/opencv_ws/opencv_ws/피부톤.jpeg"
using namespace cv;
using namespace std;
Mat src, hsv, mask;
Point p1(0, 0);
Point p2(0, 0);
int low = 20, up = 20;

void Hist_and_Backproj( );
void showNewImg();
void pickPoint (int event, int x, int y, int, void* );




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

void pickPoint (int event, int x, int y, int, void* )
{
    if( event != EVENT_LBUTTONDOWN )
    {
        return;
    }

    // Fill and get the mask
    Point seed = Point( x, y );

    int newMaskVal = 255;
    Scalar newVal = Scalar( 120, 120, 120 );

    int connectivity = 8;
    int flags = connectivity + (newMaskVal << 8 ) + FLOODFILL_FIXED_RANGE + FLOODFILL_MASK_ONLY;

    Mat mask2 = Mat::zeros( src.rows + 2, src.cols + 2, CV_8U );
    floodFill( src, mask2, seed, newVal, 0, Scalar( low, low, low ), Scalar( up, up, up), flags );
    mask = mask2( Range( 1, mask2.rows - 1 ), Range( 1, mask2.cols - 1 ) );

    imshow( "Mask", mask );

    Hist_and_Backproj( );
}

int main(int argc, char ** argv)
{
    src = imread(SKIN);
    
    cvtColor(src, hsv, COLOR_BGR2HSV);
    
    imshow("Source image", src);
    
    setMouseCallback("Source image", onMouse,0);
    
    waitKey();
    return 0;
}

void Hist_and_Backproj( )
{
    cv::VideoCapture cap(0);
    
    if(!cap.isOpened())
    {
        printf("Cant open the camera");
        exit(0);
    }
    
    cv::Mat test_image1;
    
    while(1)
    {
        cap >> test_image1;
        cv::imshow("real time", test_image1);
        
        cv::Mat hsv_image1;
        
        cvtColor(test_image1, hsv_image1, COLOR_BGR2HSV);
        cv::Mat histogramH, histogramS;
        Mat hist;
        int h_bins = 30; int s_bins = 32;
        int histSize[] = { h_bins, s_bins };

        float h_range[] = { 0, 180 };
        float s_range[] = { 0, 256 };
        const float* ranges[] = { h_range, s_range };

        int channels[] = { 0, 1 };

        /// Get the Histogram and normalize it
        calcHist( &hsv_image1, 1, channels, Mat(), hist, 2, histSize, ranges, true, false );

        normalize( hist, hist, 0, 255, NORM_MINMAX, -1, Mat() );

        /// Get Backprojection
        Mat backproj;
        calcBackProject( &hsv_image1, 1, channels, hist, backproj, ranges, 1, true );

        /// Draw the backproj
        imshow( "BackProj", backproj );
        
        if(waitKey(5) >=0)
            break;
    }
    
    

}
