#include <iostream>
#include <opencv2/opencv.hpp>
#include <cmath>

#define SOURCE1 "/Users/minsu/Desktop/대학생 자료/2학년/robotics 인턴/opencv_ws/week2/횡단보도1.jpeg"
#define SOURCE2 "/Users/minsu/Desktop/대학생 자료/2학년/robotics 인턴/opencv_ws/week2/횡단보도2.jpeg"
#define SOURCE3 "/Users/minsu/Desktop/대학생 자료/2학년/robotics 인턴/opencv_ws/week2/횡단보도3.png"
#define SOURCE4 "/Users/minsu/Desktop/대학생 자료/2학년/robotics 인턴/opencv_ws/week2/횡단보도4.jpeg"
#define SOURCE5 "/Users/minsu/Desktop/대학생 자료/2학년/robotics 인턴/opencv_ws/week2/횡단보도5.jpeg"
#define SOURCE6 "/Users/minsu/Desktop/대학생 자료/2학년/robotics 인턴/opencv_ws/week2/횡단보도6.jpeg"
#define TH 255
using namespace cv;
using namespace std;

void Hough(cv::Mat img_original,cv::Mat img_canny, int row, int col, int
           Threshold)
{
    double hough_height = sqrt(pow(row,2) + pow(col,2));
    
    int center_x = row / 2.0;
    int center_y = col / 2.0;
    
    printf("row = %d, col = %d\n",row, col);
    
    int array_angle = 180;
    int array_r = hough_height * 2;
    
    int array_size = array_angle * array_r;
    cv::Mat array = cv::Mat::zeros(array_angle, array_r, CV_8SC1);
    
    double DEG2RAD = CV_PI / 180;
    
    for(int y=0 ; y < row ; y++)
        for(int x=0 ; x < col ; x++)
        {
            if(img_canny.at<uchar>(y,x) > 0)
                for( int angle = 0; angle < 180; angle++)
                {
                    int r = (x-center_x)*cos(angle*DEG2RAD) + (y-center_y)*sin(angle*DEG2RAD);
                    
                    r = r + hough_height;
                    array.at<uchar>(angle,r) +=1;
                }
        }
    
    int max = -1 ;
    for(int y = 0; y < array_r ; y++)
        for(int x = 0; x < array_angle ; x++)
        {
            if(array.at<uchar>(x,y) > max)
            {
                max = array.at<uchar>(x,y);
            }
        }
    
    cv::Mat img_array = cv::Mat(array_r, array_angle, CV_8UC3); // 수정 : 변경할 수도 있음
    
    for(int y=0; y< array_r ; y++)
        for(int x = 0 ; x < array_angle ; x++)
        {
            int value = TH * ((double)array.at<uchar>(x,y)) / max;
            
            img_array.at<Vec3b>(y,x)[0] = TH-value;
            img_array.at<Vec3b>(y,x)[1] = TH-value;
            img_array.at<Vec3b>(y,x)[2] = TH-value;
        }
    
    int count =0;
    for (int r = 0 ; r < array_r ; r++)
        for(int angle = 0 ; angle < 180 ; angle ++)
        {
            if(array.at<uchar>(angle, r) > Threshold)
            {
                int max = array.at<uchar>(angle, r);
                for(int y = -5 ; y <= 5 ; y++)
                {
                    for (int x = -5 ; x <= 5; x++)
                    {
                        int new_r = r +y;
                        int new_angle = angle + x;
                        
                        if( new_angle < 0)
                        {
                            new_angle = 180 + new_angle;
                        }
                        else if (new_angle >= 180)
                        {
                            new_angle = new_angle - 180;
                        }
                        
                        if( new_r >=0 && new_r < array_r)
                        {
                            if(array.at<uchar>(new_angle, new_r) > max)
                            {
                                max = array.at<uchar>(new_angle,new_r);
                                x=y= 6;
                            }
                        }
                    }
                }
                
                if (max > array.at<uchar>(angle,r))
                {
                    continue;
                }
                
                int x1, x2, y1, y2;
                
                if(angle >= 45 && angle <= 135)
                {
                    x1 = 0;
                    x2 = col;
                    y1 = ((r-hough_height) - (x1 - center_x)*cos(angle*DEG2RAD)) / sin(angle*DEG2RAD) + center_y;
                    y2 = ((r-hough_height) - (x2 - center_x)*cos(angle*DEG2RAD)) / sin(angle*DEG2RAD) + center_y;
                }
                else
                {
                    y1 = 0;
                    y2 = row;
                    x1 = ((r - hough_height) - (y1 - center_y)*sin(angle*DEG2RAD)) / cos(angle*DEG2RAD) + center_x;
                    x2 = ((r - hough_height) - (y2 - center_y)*sin(angle*DEG2RAD)) / cos(angle*DEG2RAD) + center_x;
     
                }
                
                
                circle(img_array, cv::Point(angle, r), 3, Scalar(255,0,0));
                line(img_original, cv::Point(x1, y1), cv::Point(x2,y2), Scalar(255,0,0),1);
            }
        }
    imshow("img_result", img_original);

    imshow("img_array", img_array);
    imshow("img_canny", img_canny);
 
 
    //키보드 입력이 될때까지 대기
    waitKey(0);
 
 
    
}

int main(int argc, char ** argv)
{
    cv::Mat img = cv::imread(SOURCE1);
    
    cv::Mat img_gray;
    cv::cvtColor(img,img_gray, cv::COLOR_BGR2GRAY);
    
    cv::Mat img_canny;
    cv::Canny(img_gray, img_canny, 150, 255);

    int row = img_canny.rows;
    int col = img_canny.cols;

    Hough(img,img_canny, row,col,110);
    
}
