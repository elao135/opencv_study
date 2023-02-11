#include <iostream>
#include <opencv2/opencv.hpp>
#include<iomanip>
#include<string>
#include<algorithm>
#include<vector>


#define BANANA "/Users/minsu/Desktop/대학생 자료/2학년/robotics 인턴/opencv_ws/week3/과일 사진/바나나"
#define APPLE "/Users/minsu/Desktop/대학생 자료/2학년/robotics 인턴/opencv_ws/week3/과일 사진/사과"
#define GRAPE "/Users/minsu/Desktop/대학생 자료/2학년/robotics 인턴/opencv_ws/week3/과일 사진/포도"

#define RANDOM "/Users/minsu/Desktop/대학생 자료/2학년/robotics 인턴/opencv_ws/week3/과일 사진/random"

using namespace cv;
using namespace std;

int main(int argc, char ** argv)
{
    cv::Mat image;
    cv::Mat image_gray;
    cv::Mat img_canny;
    cv::Mat draw = cv::Mat(2000,2000,CV_8UC3);
//    for(int i=1; i< 30; i++)
//    {
//        std::stringstream image_name;
//        image_name << GRAPE << "/images-" << i << ".jpg";
//        image = cv::imread(image_name.str(), cv::COLOR_BGR2GRAY);
//        cv::cvtColor(image,image_gray, cv::COLOR_BGR2GRAY);
//        cv::Canny(image, img_canny, 150, 255);
//
//        int center_x = img_canny.rows/2;
//        int center_y = img_canny.cols/2;
//        int center_to_edge;
//        int sum=0;
//        int count=0;
//        for(int j=0 ; j<img_canny.rows; j++)
//        {
//            for(int k=0; k< img_canny.cols; k++)
//            {
//                if(img_canny.at<uchar>(j,k) ==255)
//                {
//                    center_to_edge = sqrt(pow(center_x-j,2)+pow(center_y-k,2));
//                    sum+= center_to_edge;
//                    count++;
//                }
//            }
//        }
//
//        int avg = sum/count;
//
//        double vari = 0;
//
//        for(int j=0 ; j<img_canny.rows; j++)
//        {
//            for(int k=0; k< img_canny.cols; k++)
//            {
//                if(img_canny.at<uchar>(j,k) ==255)
//                {
//                    center_to_edge = sqrt(pow(center_x-j,2)+pow(center_y-k,2));
//                    vari += pow(center_to_edge - avg, 2);
//                }
//
//            }
//        }
//
//        vari = vari/count;
//
//        double der = sqrt(vari);
//
//        printf("분산 :%f \n", vari);
//        printf("표준편차 : %f \n", der);
//
//        cv::circle(draw, cv::Point(vari,der*3), 3, Scalar(255,0,0));
//    }
    for(int i=1; i< 30; i++)
    {
        std::stringstream image_name;
        image_name << BANANA << "/images-" << i << ".jpg";
        image = cv::imread(image_name.str(), cv::COLOR_BGR2GRAY);
        cv::cvtColor(image,image_gray, cv::COLOR_BGR2GRAY);
        cv::Canny(image, img_canny, 150, 255);
        
        int center_x = img_canny.rows/2;
        int center_y = img_canny.cols/2;
        int center_to_edge;
        int sum=0;
        int count=0;
        for(int j=0 ; j<img_canny.rows; j++)
        {
            for(int k=0; k< img_canny.cols; k++)
            {
                if(img_canny.at<uchar>(j,k) ==255)
                {
                    center_to_edge = sqrt(pow(center_x-j,2)+pow(center_y-k,2));
                    sum+= center_to_edge;
                    count++;
                }
            }
        }
        
        int avg = sum/count;
        
        double vari = 0;
        
        for(int j=0 ; j<img_canny.rows; j++)
        {
            for(int k=0; k< img_canny.cols; k++)
            {
                if(img_canny.at<uchar>(j,k) ==255)
                {
                    center_to_edge = sqrt(pow(center_x-j,2)+pow(center_y-k,2));
                    vari += pow(center_to_edge - avg, 2);
                }

            }
        }
        
        vari = vari/count;
        
        double der = sqrt(vari);
        
        printf("분산 :%f \n", vari);
        printf("표준편차 : %f \n", der);
        cv::circle(draw, cv::Point(vari,der*3), 3, Scalar(0,255,0));
    }
    for(int i=1; i< 30; i++)
    {
        std::stringstream image_name;
        image_name << APPLE << "/images-" << i << ".jpg";
        image = cv::imread(image_name.str(), cv::COLOR_BGR2GRAY);
        cv::cvtColor(image,image_gray, cv::COLOR_BGR2GRAY);
        cv::Canny(image_gray, img_canny, 150, 255);
        
        int center_x = img_canny.rows/2;
        int center_y = img_canny.cols/2;
        int center_to_edge;
        int sum=0;
        int count=0;
        for(int j=0 ; j<img_canny.rows; j++)
        {
            for(int k=0; k< img_canny.cols; k++)
            {
                if(img_canny.at<uchar>(j,k) ==255)
                {
                    center_to_edge = sqrt(pow(center_x-j,2)+pow(center_y-k,2));
                    sum+= center_to_edge;
                    count++;
                }
            }
        }
        
        int avg = sum/count;
        
        double vari = 0;
        int max =1;
        int min = -1;
        for(int j=0 ; j<img_canny.rows; j++)
        {
            for(int k=0; k< img_canny.cols; k++)
            {
                if(img_canny.at<uchar>(j,k) ==255)
                {
                    center_to_edge = sqrt(pow(center_x-j,2)+pow(center_y-k,2));
                    vari += pow(center_to_edge - avg, 2);
                    
                    if(vari>max)
                        max = vari;
                    if(vari<min)
                        min = vari;
                }

            }
        }
        
        vari = vari/count;
        
        double der = sqrt(vari);
        
        printf("분산 :%f \n", (vari-min)/(max-min)*10000);
        printf("표준편차 : %f \n", der*3);
        cv::circle(draw, cv::Point(vari,der*3), 3, Scalar(0,0,255));
    }
    
    cv::imshow("og", draw);
    cv::waitKey(0);
    
    
    
}
