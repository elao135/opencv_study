#include <iostream>
#include <opencv2/opencv.hpp>

#define TEST_IMAGE1 "/Users/minsu/Desktop/대학생 자료/2학년/robotics 인턴/opencv_ws/opencv_ws/black.jpeg"
#define TEST_IMAGE2 "/Users/minsu/Desktop/대학생 자료/2학년/robotics 인턴/opencv_ws/opencv_ws/white.jpeg"
#define LENNA_IMAGE "/Users/minsu/Desktop/대학생 자료/2학년/robotics 인턴/opencv_ws/opencv_ws/Lenna.png"
#define NASA "/Users/minsu/Desktop/대학생 자료/2학년/robotics 인턴/opencv_ws/opencv_ws/test.jpeg"

#define BIN 2

using namespace std;
using namespace cv;

void draw_histogram(int histogram[])
{
    int hist_w = 256*BIN;
    int hist_h = 500;
    
    cv::Mat histogram_image(hist_h, hist_w, CV_8UC1, Scalar(255,255,255));
    
    int max = 0;
    
    for(int i=0; i<256; i++)
    {
        if (max < histogram[i])
        {
            max = histogram[i];
        }
    }
    
    for(int i=0 ; i<256 ; i++)
    {
        histogram[i]  = cvRound(((double)histogram[i]/max)*hist_h);
    }
    
    for (int i=0; i<256; i++)
    {
        line(histogram_image, Point(i*BIN,hist_h),Point(i*BIN,hist_h-histogram[i]),Scalar(0, 0, 255));
    }
    cv::imshow("Histogram", histogram_image);
    cv::waitKey(0);
    
    
}
void draw_equlization(int histogram[], cv::Mat test_image1)
{
    int hist_w = 256*BIN;
    int hist_h = 500;
    cv::Mat equlization_image(hist_h, hist_w, CV_8UC1, Scalar(255,255,255));
    
    int sumHistogram[256]; //누적값
    
    int round[256];
    
    int pixel_num = 0;
    
    for(int i=0; i<256;i++)
    {
        pixel_num+=histogram[i];
    }

    for (int i=0 ; i<256; i++)
    {
        sumHistogram[i] =0;
    }
    
    for (int i=0 ; i<256; i++)
    {
        for( int j=0 ; j<i+1; j++)
        {
            sumHistogram[i] += histogram[j];
        }
        round[i] = cvRound((double)(sumHistogram[i]*255)/pixel_num);
    }
    
    for(int i=0; i<256; i++)
    {
        histogram[i] = 0;
    }
    
    for (int row = 0 ; row < test_image1.rows; row++)
    {
        for (int col = 0 ; col < test_image1.cols; col++)
        {
            histogram[round[test_image1.at<uchar>(row,col)]]++;
        }
    }
    
    int max = 0;
    
    for(int i=0; i<256; i++)
    {
        if (max < histogram[i])
        {
            max = histogram[i];
        }
    }
    
    for(int i=0 ; i<256 ; i++)
    {
        histogram[i]  = cvRound(((double)histogram[i]/max)*hist_h);
    }
    
    for (int i=0; i<256; i++)
    {
        line(equlization_image, Point(i*BIN,hist_h),Point(i*BIN,hist_h-histogram[i]),Scalar(0, 0, 255));
    }
    cv::imshow("equlization", equlization_image);
    cv::waitKey(0);
    
}
int main(int argc, char ** argv)
{
    cv::Mat test_image1 = cv::imread(LENNA_IMAGE);
    
    int h[256];
    
    for(int i=0; i<256; i++)
    {
        h[i] = 0;
    }
    
    for (int row = 0 ; row < test_image1.rows; row++)
    {
        for (int col = 0 ; col < test_image1.cols; col++)
        {
            h[test_image1.at<uchar>(row,col)]++;
            
        }
    }
    
    draw_histogram(h);
    
    
    draw_equlization(h, test_image1);
}
