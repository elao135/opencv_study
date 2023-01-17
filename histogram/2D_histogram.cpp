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

#define SCALE 0.2


int main(int argc, char ** argv)
{
    cv::Mat test_image1 = cv::imread(LENNA_IMAGE);
    cv::Mat hsv_image1;
    
    cvtColor(test_image1, hsv_image1, COLOR_BGR2HSV);
    cv::Mat histogramH, histogramS;
    
    vector<Mat> hsv_planes;
    split(hsv_image1, hsv_planes);

    equalizeHist(hsv_planes[0], hsv_planes[0]);
    equalizeHist(hsv_planes[1], hsv_planes[1]);
    merge(hsv_planes, hsv_image1);
    
    const int channel_numberH[] = {0};
    const int channel_numberS[] = {1};
    
    float channel_rangeH[] = {0.0, 180.0};
    float channel_rangeS[] = {0.0, 255.0};
    const float * channel_rangesH = channel_rangeH;
    const float * channel_rangesS = channel_rangeS;
    int number_binsH = 180;
    int number_binsS = 255;
    
    cv::calcHist(&hsv_image1,1, channel_numberH, Mat(), histogramH,1,&number_binsH, &channel_rangesH);
    cv::calcHist(&hsv_image1,1, channel_numberS, Mat(), histogramS,1,&number_binsS, &channel_rangesS);
    
    int hist_w = 512; int hist_h = 400;
    int bin_wH = cvRound((double)hist_w / number_binsH);
    int bin_wS = cvRound((double)hist_w / number_binsS);
    cv::Mat histImageH(hist_h, hist_w, CV_8UC3, Scalar(0,0,0));
    normalize(histogramH, histogramH, 0, histImageH.rows, NORM_MINMAX);
    
    cv::Mat histImageS(hist_h, hist_w, CV_8UC3, Scalar(0,0,0));
    normalize(histogramS, histogramS, 0, histImageS.rows, NORM_MINMAX);
    
    for (int i=1 ; i<number_binsH; i++)
    {
        cv::line(histImageH, Point(bin_wH*(i-1), hist_h - cvRound(histogramH.at<float>(i-1))),Point(bin_wH*(i), hist_h - cvRound(histogramH.at<float>(i))),Scalar(255,0,0), 2,8,0);
    }
    
    for (int i=1 ; i<number_binsS; i++)
    {
        cv::line(histImageS, Point(bin_wS*(i-1), hist_h - cvRound(histogramS.at<float>(i-1))),Point(bin_wS*(i), hist_h - cvRound(histogramS.at<float>(i))),Scalar(255,0,0), 2,8,0);
    }
    
    
    namedWindow("Original", WINDOW_AUTOSIZE);
    namedWindow("HistogramH", WINDOW_AUTOSIZE);
    namedWindow("HistogramS", WINDOW_AUTOSIZE);
    
    imshow("Original", test_image1);
    imshow("HistogramH", histImageH);
    imshow("HistogramS", histImageS);
    
    cv::waitKey(0);
    return 0;
}

