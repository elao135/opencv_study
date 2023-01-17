#include "opencv2/imgproc.hpp"
#include "opencv2/imgcodecs.hpp"
#include "opencv2/highgui.hpp"
#include <iostream>
#define TEST_IMAGE1 "/Users/minsu/Desktop/대학생 자료/2학년/robotics 인턴/opencv_ws/opencv_ws/black.jpeg"
#define TEST_IMAGE2 "/Users/minsu/Desktop/대학생 자료/2학년/robotics 인턴/opencv_ws/opencv_ws/white.jpeg"
#define LENNA_IMAGE "/Users/minsu/Desktop/대학생 자료/2학년/robotics 인턴/opencv_ws/opencv_ws/Lenna.png"
#define NASA "/Users/minsu/Desktop/대학생 자료/2학년/robotics 인턴/opencv_ws/opencv_ws/test.jpeg"
using namespace cv;
using namespace std;

#define SCALE 0.2

int main(int argc, char ** argv)
{
    cv::VideoCapture cap(0);
    
    if(!cap.isOpened())
    {
        printf("Cant open the camera");
        return -1;
    }
    
    cv::Mat test_image1;
    
    while (1)
    {
        cap >> test_image1;
        cv::imshow("real time", test_image1);
        
        cv::Mat hsv_image1;
        
        cvtColor(test_image1, hsv_image1, COLOR_BGR2HSV);
        Mat histogramH, histogramS;
        
        vector<Mat> hsv_planes;
        split(hsv_image1, hsv_planes);
        
    //    equalizeHist(hsv_planes[0], hsv_planes[0]);
    //    equalizeHist(hsv_planes[1], hsv_planes[1]);
        merge(hsv_planes, hsv_image1);
        
        const int channel_numberH[] = {0};
        const int channel_numberS[] = {1};
        
        float channel_range[] = {0.0, 255.0};
        const float * channel_ranges = channel_range;
        int number_bins = 255;
        
        cv::calcHist(&hsv_image1,1, channel_numberH, Mat(), histogramH,1,&number_bins, &channel_ranges);
        cv::calcHist(&hsv_image1,1, channel_numberS, Mat(), histogramS,1,&number_bins, &channel_ranges);
        
        int hist_w = 512; int hist_h = 400;
        int bin_w = cvRound((double)hist_w / number_bins);
        
        cv::Mat histImageH(hist_h, hist_w, CV_8UC3, Scalar(0,0,0));
        normalize(histogramH, histogramH, 0, histImageH.rows, NORM_MINMAX, -1, Mat());
        
        cv::Mat histImageS(hist_h, hist_w, CV_8UC3, Scalar(0,0,0));
        normalize(histogramS, histogramS, 0, histImageS.rows, NORM_MINMAX, -1, Mat());
        
        for (int i=1 ; i<number_bins; i++)
        {
            cv::line(histImageH, Point(bin_w*(i-1), hist_h - cvRound(histogramH.at<float>(i-1))),Point(bin_w*(i), hist_h - cvRound(histogramH.at<float>(i))),Scalar(255,0,0), 2,8,0);
            cv::line(histImageS, Point(bin_w*(i-1), hist_h - cvRound(histogramS.at<float>(i-1))),Point(bin_w*(i), hist_h - cvRound(histogramS.at<float>(i))),Scalar(255,0,0), 2,8,0);
        }
        
        

        namedWindow("HistogramH", WINDOW_AUTOSIZE);
        namedWindow("HistogramS", WINDOW_AUTOSIZE);
        
        

        imshow("HistogramH", histImageH);
        imshow("HistogramS", histImageS);
        
        if(waitKey(5) >= 0)
            break;
        
    }
    return 0;
}
