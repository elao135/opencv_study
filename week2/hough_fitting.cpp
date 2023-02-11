#include <iostream>
#include <opencv2/opencv.hpp>
#include <cmath>

#define SOURCE1 "/Users/minsu/Desktop/대학생 자료/2학년/robotics 인턴/opencv_ws/week2/reference_fiqure.jpg"
#define REFERENCE "/Users/minsu/Desktop/대학생 자료/2학년/robotics 인턴/opencv_ws/week2/fiqure.jpg"
#define SOURCE "/Users/minsu/Desktop/대학생 자료/2학년/robotics 인턴/opencv_ws/week2/fiqure2.jpg"

#define REFERENCE2 "/Users/minsu/Desktop/대학생 자료/2학년/robotics 인턴/opencv_ws/week2/refer2.jpg"
#define SOURCE2 "/Users/minsu/Desktop/대학생 자료/2학년/robotics 인턴/opencv_ws/week2/source2.jpg"

#define REFERENCE3 "/Users/minsu/Desktop/대학생 자료/2학년/robotics 인턴/opencv_ws/week2/refer3.jpg"
#define SOURCE3 "/Users/minsu/Desktop/대학생 자료/2학년/robotics 인턴/opencv_ws/week2/source3.jpg"

#define REFERENCE4 "/Users/minsu/Desktop/대학생 자료/2학년/robotics 인턴/opencv_ws/week2/REFERENCCE4.jpg"
#define SOURCE4 "/Users/minsu/Desktop/대학생 자료/2학년/robotics 인턴/opencv_ws/week2/SOURCE4.jpg"

#define REFERENCE5 "/Users/minsu/Desktop/대학생 자료/2학년/robotics 인턴/opencv_ws/week2/refer5.jpg"
#define SOURCE5 "/Users/minsu/Desktop/대학생 자료/2학년/robotics 인턴/opencv_ws/week2/source5.jpg"

#define REFERENCE6 "/Users/minsu/Desktop/대학생 자료/2학년/robotics 인턴/opencv_ws/week2/refer6.jpg"
#define SOURCE6 "/Users/minsu/Desktop/대학생 자료/2학년/robotics 인턴/opencv_ws/week2/source6.jpg"

#define REFERENCE7 "/Users/minsu/Desktop/대학생 자료/2학년/robotics 인턴/opencv_ws/week2/refer7.jpg"
#define SOURCE7 "/Users/minsu/Desktop/대학생 자료/2학년/robotics 인턴/opencv_ws/week2/source7.jpg"


#define TH 255
using namespace cv;
using namespace std;

int count = 0;

int pre = 0 ;

int angle1[180];
int angle11[180];
int angle2[180];
int angle22[180];
int angle3[180];
int angle33[180];
int key = 0;

int count1 = 0;
int count2 = 0;

void Hough(cv::Mat img_original,cv::Mat img_canny, int row, int col, int
           Threshold)
{
    

    
    double hough_height = sqrt(pow(row,2) + pow(col,2));
    
    int center_x = row / 2.0;
    int center_y = col / 2.0;
    

    
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
                
                circle(img_array, cv::Point(0, 0), 3, Scalar(0,0,255));
//                circle(img_array, cv::Point(angle, r), 3, Scalar(255,0,0));
                circle(img_array, cv::Point(angle, 100), 10, Scalar(255,0,0));
                

                count = angle;
                if(pre == 0)
                {
                    angle1[key] = angle ;
                    angle11[key] = array.at<uchar>(angle,r);
                    key++;
                    count1 ++;
                }
                
                if(pre == 1)
                {
                    angle2[key] = angle ;
                    angle22[key] = array.at<uchar>(angle,r);
                    key++;
                    count2 ++;
                }
                
                line(img_original, cv::Point(x1, y1), cv::Point(x2,y2), Scalar(255,0,0),1);
            }
        }
    imshow("img_result", img_original);

    imshow("img_array", img_array);
    imshow("img_canny", img_canny);
 
    
    waitKey(0);
    pre++;
    
    if(pre ==1)
    {
        key = 0;
    }

 
}

int main(int argc, char ** argv)
{
    cv::Mat img1 = cv::imread(REFERENCE7);
    cv::Mat img2 = cv::imread(SOURCE7);
    
    cv::Mat img1_gray;
    cv::Mat img2_gray;
    cv::cvtColor(img1,img1_gray, cv::COLOR_BGR2GRAY);
    cv::cvtColor(img2,img2_gray, cv::COLOR_BGR2GRAY);
    
    for(int i=0 ; i< 180 ; i++)
    {
        angle1[i]= 0;
        angle2[i]= 0;
        angle3[i]= 0;
    }
    
    cv::Mat img_canny1;
    cv::Mat img_canny2;
    cv::Canny(img1_gray, img_canny1, 150, 255);
    cv::Canny(img2_gray, img_canny2, 150, 255);
    int row1 = img_canny1.rows;
    int col1 = img_canny1.cols;
    
    int row2 = img_canny2.rows;
    int col2 = img_canny2.cols;

    Hough(img1,img_canny1, row1,col1,105);
    Hough(img2,img_canny2, row2,col2,105);
    
    int differ = 0;
    
    for(int i=0 ; i< count1; i++)
    {
        for(int j=0; j< count2; j++)
        {
            differ = angle1[i] - angle2[j];
            
            if(differ < 0)
            {
                differ -=differ*2;
            }
            
            if(differ > 180)
            {
                differ = 180-differ;
            }
            angle3[differ]+=  angle11[i]*angle11[i];
            
        }
    }
    int max = 0;
    for(int i=0; i<180; i++)
    {
        if(angle3[i] >= angle3[max])
        {
            max = i;
        }
        printf("angle3[%d] = %d\n", i,angle3[i]);
    }
    printf("max = %d\n", max);
    
    Point center = Point(img2.cols/2, img2.rows/2);
    double angle = 45.0;
    double scale = 1.0;
    cv::Mat dst;
    
    cv::Mat rot_mat = getRotationMatrix2D(center, max, scale);
    warpAffine(img2, dst, rot_mat, img2.size());
    
    imshow("og",img1);
    imshow("dst", dst);
    waitKey(0);
    
    return 0;
    
    
}

