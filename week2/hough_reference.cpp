#include <opencv2/highgui.hpp>
#include <opencv2/imgproc.hpp>
#include <iostream>
#include <stdio.h>

#define SOURCE "/Users/minsu/Desktop/대학생 자료/2학년/robotics 인턴/opencv_ws/week2/횡단보도1.jpeg"
#define TH 255
using namespace cv;
using namespace std;
 
 
int main(int argc, char** argv)
{
 
    Mat img_original, img_gray, img_edge;
 
    //이미지파일 로드
    img_original = imread(SOURCE, IMREAD_COLOR);
    //img_original = imread("test2.png", IMREAD_COLOR);
    //img_original = imread("test.jpg", IMREAD_COLOR);
    if (img_original.empty())
    {
        cout << "Could not open or find the image" << std::endl;
        return -1;
    }
 
 
    //그레이스케일 이미지로 변환
    cvtColor(img_original, img_gray, COLOR_BGR2GRAY);
 
    //에지 검출
    GaussianBlur(img_gray, img_edge, cv::Size(5, 5),0,0);
    Canny(img_edge, img_edge, 50, 150, 3);
 
 
    int height = img_edge.rows;
    int width = img_edge.cols;
 
    double hough_height = ((sqrt(2.0) * (double)(height>width ? height:width)) / 2.0);
    
//    double hough_height = ((sqrt(2.0) * (height*height+width*width)));
    
    int centerX = width / 2.0;
    int centerY = height / 2.0;
 
 
    int accumulator_width = 180;
    int accumulator_height = hough_height * 2;
    int accumulator_size = accumulator_height * accumulator_width;
    int *accumulator = (int*)malloc(sizeof(int)*accumulator_size);
    double DEG2RAD = CV_PI / 180;
    
    for (int y = 0; y < height; y++)
    {
        for (int x = 0; x < width; x++)
        {
            if ( img_edge.at<uchar>(y,x) > 0 )
                for (int angle = 0; angle < 180; angle++)
                {
                    int r = (x-centerX)*cos(angle*DEG2RAD) + (y-centerY)*sin(angle*DEG2RAD);
 
                    r = r + hough_height;//r이 음수인 경우 때문 -r ~ r 범위를 0 ~ 2r 범위로 변경
                    accumulator[r*accumulator_width + angle] += 1;
                }
        }
    }
        
 
    //accumulator에서 MAX값 찾기
    int max = -1;
    for (int y = 0; y < accumulator_height; y++)
    for (int x = 0; x < accumulator_width; x++)
    {
        if (accumulator[y*accumulator_width + x] > max)
            max = accumulator[y*accumulator_width + x];
    }
    
 
 
    //accumulator를 이미지화
    Mat img_accumulator = Mat(accumulator_height, accumulator_width, CV_8UC3);
 
    for (int y = 0; y < accumulator_height; y++)
    for (int x = 0; x < accumulator_width; x++)
    {
        int value = TH * ((double)accumulator[y*accumulator_width + x]) / max;
        
        img_accumulator.at<Vec3b>(y, x)[0] = TH-value;
        img_accumulator.at<Vec3b>(y, x)[1] = TH-value;
        img_accumulator.at<Vec3b>(y, x)[2] = TH-value;
 
    }
 
 
 
    
    int count = 0;
    for (int r = 0; r < accumulator_height; r++)
    for (int angle = 0; angle < 180; angle++)
    {
 
        if (accumulator[r * accumulator_width + angle] > 110) //threshold
        {
 
            // 11 x 11 영역내에서 현재 위치가 local maxima 인지 검사
            int max = accumulator[r * accumulator_width + angle];
            for (int y = -5; y <= 5; y++)
            {
                for (int x = -5; x <= 5; x++)
                {
                    int new_r = r + y;
                    int new_angle = angle + x;
 
                    if ( new_angle  < 0 )
                    {
                        new_angle = 180 + new_angle;
                    }
                    else if (new_angle >= 180) {
                        new_angle = new_angle - 180;
                    }
                    
                    
                    if ( new_r >= 0 && new_r < accumulator_height)
                    {
                        if (accumulator[ new_r * accumulator_width + new_angle] > max)
                        {
                            max = accumulator[ new_r * accumulator_width + new_angle];
                            x = y = 6;//loop 종료
                        }
                    }
                }
            }
 
            if (max > accumulator[r * accumulator_width + angle])
            {
                continue; //현재 위치는 local maxima가 아님
            }
 
 
            // r = x*cos(theta) + y*sin(theta)
            // y = (r- x*cos(theta))/ sin(theta) 수평선인 경우
            // x = (r- y*sin(theta))/ cos(theta) 수직선인 경우
 
            int x1, x2, y1, y2;
 
            if (angle >= 45 && angle <= 135) //수평선
            {
                x1 = 0;
                x2 = width;
                y1 = ((r - hough_height) - (x1 - centerX)*cos(angle*DEG2RAD)) / sin(angle*DEG2RAD) + centerY;
                y2 = ((r - hough_height) - (x2 - centerX)*cos(angle*DEG2RAD)) / sin(angle*DEG2RAD) + centerY;
            }
            else //수직선
            {
                y1 = 0;
                y2 = height;
                x1 = ((r - hough_height) - (y1 - centerY)*sin(angle*DEG2RAD)) / cos(angle*DEG2RAD) + centerX;
                x2 = ((r - hough_height) - (y2 - centerY)*sin(angle*DEG2RAD)) / cos(angle*DEG2RAD) + centerX;
 
            }
 
            circle(img_accumulator, cv::Point(angle, r), 3, Scalar(255, 0, 0));
            line(img_original, cv::Point(x1, y1), cv::Point(x2, y2), Scalar(255, 0, 0), 1);
            count++;
 
            cout << count << " (" << x1 << "," << y1 << ") (" << x2 << "," << y2 << ")  angle=" << angle<<" r="<<r<< " accumulator값="<< accumulator[r * accumulator_width + angle]<<endl;
        }
 
    }
 
    
 
    imshow("img_result", img_original);
    imshow("img_gray", img_gray);
    imshow("img_edge", img_edge);
    imshow("img_accumulator", img_accumulator);
 
    imwrite("img_gray.jpg", img_gray);
    imwrite("img_edge.jpg", img_edge);
    imwrite("img_accumulator.jpg", img_accumulator);
    imwrite("img_result.jpg", img_original);
 
 
    //키보드 입력이 될때까지 대기
    waitKey(0);
 
 
    return 0;
}
