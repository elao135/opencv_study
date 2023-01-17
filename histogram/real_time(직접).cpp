#include <opencv2/opencv.hpp>
#include <iostream>
#define BIN 2

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

int main(int argc, char ** argv)
{
    cv::VideoCapture cap(0);
    
    if(!cap.isOpened())
    {
        printf("Cant open the camera");
        return -1;
    }
    
    cv::Mat img;
    
    int h[256];
    
    for(int i=0; i<256; i++)
    {
        h[i] = 0;
    }
    
    while (1)
    {
        cap >> img;
        cv::imshow("real time", img);
        
        if(cv::waitKey(1) == 27)
            break;
        
        for (int row = 0 ; row < img.rows; row++)
        {
            for (int col = 0 ; col < img.cols; col++)
            {
                h[img.at<uchar>(row,col)]++;
            }
        }
        
        draw_histogram(h);
        
    }
    return 0;
}
