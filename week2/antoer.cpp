#include <iostream>
#include <opencv2/opencv.hpp>
#define SOURCE "/Users/minsu/Desktop/대학생 자료/2학년/robotics 인턴/opencv_ws/week2/횡단보도1.jpeg"
#include <stdlib.h>
using namespace std;
using namsspace cv;
void Hough_by_minsu(cv::Mat img_canny, int w, int h)
{
    double houghH = ((sqrt(2.0) * (double)(h>w?h:w)) / 2.0);
    int accH = houghH * 2.0;
    int accW = 180;
    
    int *accumulator = (int*)malloc(sizeof(int)*(accH * accW));
    
    double centerX = w/2;
    double centerY = h/2;
    
    double DEG2RAD = CV_PI / 180;
    
    for(int y=0; y<h ; y++)
    {
        for(int x=0; x<w ; x++)
        {
            if(img_canny.at<uchar>(y,x) > 0)
            {
                for ( int angle = 0; angle<180; angle++)
                {
                    double r = ((double)x - centerX) * cos((double)angle * DEG2RAD) + (((double)y - centerY) * sin((double)angle * DEG2RAD));
                    accumulator[(int)(cvRound(r + houghH) * 180.0) + angle] +=1;
                }
            }
        }
    }
    
    int max = 0 ;
    
    for(int y=0 ; y< accH ; y++)
    {
        for(int x = 0 ; x < accW ; x++)
        {
            if(accumulator[y*accW + x] >max)
                max = accumulator[y*accW + x];
        }
    }
    
    cv::Mat img_accmulator = cv::Mat(accH, accW, CV_8UC3);
    
    for (int y=0 ; y < accH ; y++)
    {
        for(int x = 0 ; x < accW ; x++)
        {
            int value = 255 * ((double)accumulator[y*accW + x]) / max;
            
            img_accmulator.at<cv::Vec3b>(y,x)[0] = 255-value;
            img_accmulator.at<cv::Vec3b>(y,x)[0] = 255-value;
            img_accmulator.at<cv::Vec3b>(y,x)[0] = 255-value;
        }
    }
}

int main(int argc, char ** argv)
{
    cv::Mat img = cv::imread(SOURCE);
    cv::Mat img_gray;
    cv::cvtColor(img, img_gray, cv::COLOR_BGR2GRAY);
    cv::Mat img_canny;
    cv::Canny(img_gray, img_canny, 100, 150);
    
    int w = img_canny.cols;
    int h = img_canny.rows;
    
    Hough_by_minsu(img_canny, w, h);
}
