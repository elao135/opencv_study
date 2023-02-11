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

using namespace std;;
using namespace cv;;


class pos{
public:
    double x;
    double y;
    double z;
};

double tem_distance1;
double tem_distance2;
double tem_distance3;

pos center1;
pos center2;
pos center3;

int main(int argc, char ** argv)
{
    cv::Mat image;
    cv::Mat imageCopy;
    cv::Mat image_Grape;
    cv::Mat image_Banana;
    cv::Mat image_Apple;
    vector<pos> datas;
    pos tmp;
    vector<pos>  group1;
    vector<pos>  group2;
    vector<pos>  group3;
    
    cv::Mat draw = cv::Mat(500, 500, CV_8UC3);
    for(int i=1 ; i <= 30 ; i++)
    {
        std::stringstream image_name;
        image_name << GRAPE << "/images-" << i << ".jpg";
        image = cv::imread(image_name.str(), IMREAD_COLOR);
        image_Grape = cv::imread(image_name.str(), IMREAD_COLOR);
        cv::cvtColor(image, imageCopy, COLOR_BGR2HSV);
        
        int count =0;
        double sumH = 0;
        double sumS = 0;
        double sumV = 0;
        for(int i=0; i<image.rows ; i ++)
        {
            for(int j=0 ; j<image.cols ; j++)
            {
                if(imageCopy.at<uchar>(i,j) == 255)
                    continue;
                
                int img_h = imageCopy.at<Vec3b>(i,j)[0];
                int img_s = imageCopy.at<Vec3b>(i,j)[1];
                int img_v = imageCopy.at<Vec3b>(i,j)[2];
                
                count ++;
                sumH += img_h;
                sumS += img_s;
                sumV += img_v;
            }
        }
        tmp.x = (double)(sumH/count);
        tmp.y = (double)(sumS/count);
        tmp.z = (double)(sumV/count);
        datas.push_back(tmp);
    }
    for(int i=1 ; i <= 30 ; i++)
    {
        std::stringstream image_name;
        image_name << BANANA << "/images-" << i << ".jpg";
        image = cv::imread(image_name.str(), IMREAD_COLOR);
        image_Banana = cv::imread(image_name.str(), IMREAD_COLOR);
        cv::cvtColor(image, imageCopy, COLOR_BGR2HSV);
        
        int count =0;
        double sumH = 0;
        double sumS = 0;
        double sumV = 0;
        for(int i=0; i<image.rows ; i ++)
        {
            for(int j=0 ; j<image.cols ; j++)
            {
                if(imageCopy.at<uchar>(i,j) >= 230)
                    continue;
                
                int img_h = imageCopy.at<Vec3b>(i,j)[0];
                int img_s = imageCopy.at<Vec3b>(i,j)[1];
                int img_v = imageCopy.at<Vec3b>(i,j)[2];
                
                count ++;
                sumH += img_h;
                sumS += img_s;
                sumV += img_v; 
                
            }
        }
        
        tmp.x = (double)(sumH/count);
        tmp.y = (double)(sumS/count);
        tmp.z = (double)(sumV/count);
        datas.push_back(tmp);
    }
    
    for(int i=1 ; i <= 30 ; i++)
    {
        std::stringstream image_name;
        image_name << APPLE << "/images-" << i << ".jpg";
        image = cv::imread(image_name.str(), IMREAD_COLOR);
        image_Apple = cv::imread(image_name.str(), IMREAD_COLOR);
        cv::cvtColor(image, imageCopy, COLOR_BGR2HSV);
        
        int count =0;
        double sumH = 0;
        double sumS = 0;
        double sumV = 0;
        for(int i=0; i<image.rows ; i ++)
        {
            for(int j=0 ; j<image.cols ; j++)
            {
                if(imageCopy.at<uchar>(i,j) == 255)
                    continue;
                
                int img_h = imageCopy.at<Vec3b>(i,j)[0];
                int img_s = imageCopy.at<Vec3b>(i,j)[1];
                int img_v = imageCopy.at<Vec3b>(i,j)[2];
                
                count ++;
                sumH += img_h;
                sumS += img_s;
                sumV += img_v;
            }
        }
        
        circle(draw, cv::Point(sumS/count, sumV/count), 1, Scalar(0,0,255));
        tmp.x = (double)(sumH/count);
        tmp.y = (double)(sumS/count);
        tmp.z = (double)(sumV/count);
        datas.push_back(tmp);
        
    }
    
    center1.x = 45.0;
    center1.y = 55.0;
    center1.z = 75.0;
    
    center2.x = 80.0;
    center2.y = 90.0;
    center2.z = 100.0;
    
    center3.x = 100.0;
    center3.y = 130.0;
    center3.z = 120.0;
    int count =0;
    
    while(true)
    {
        double min;
        double sum1x=0;
        double sum1y=0;
        double sum1z=0;
        double sum2x=0;
        double sum2y=0;
        double sum2z=0;
        double sum3x=0;
        double sum3y=0;
        double sum3z=0;
        for(int i=0; i<90; i++)
        {
            tem_distance1 = sqrt(pow(center1.x-datas[i].x, 2)+pow(center1.y-datas[i].y, 2)+pow(center1.z-datas[i].z, 2));
            tem_distance2 = sqrt(pow(center2.x-datas[i].x, 2)+pow(center2.y-datas[i].y, 2)+pow(center2.z-datas[i].z, 2));
            tem_distance3 = sqrt(pow(center3.x-datas[i].x, 2)+pow(center3.y-datas[i].y, 2)+pow(center3.z-datas[i].z, 2));
            min = ((tem_distance1>tem_distance2)?tem_distance2:tem_distance1)>tem_distance3 ? tem_distance3:((tem_distance1>tem_distance2)?tem_distance2:tem_distance1) ;
            
            if(min == tem_distance1)
            {
                min = tem_distance1;
                group1.push_back(datas[i]);
                
            }
            
            else if(min == tem_distance2)
            {
                min = tem_distance2;
                group2.push_back(datas[i]);
                
            }
            else
            {
                min = tem_distance3;
                group3.push_back(datas[i]);
                
            }
            
        }
        
        for(int j=0 ; j<group1.size() ; j++)
        {
            sum1x += group1[j].x;
            sum1y += group1[j].y;
            sum1z += group1[j].z;
        }
        for(int j=0 ; j<group2.size() ; j++)
        {
            sum2x += group2[j].x;
            sum2y += group2[j].y;
            sum2z += group2[j].z;
        }
        for(int j=0 ; j<group3.size() ; j++)
        {
            sum3x += group3[j].x;
            sum3y += group3[j].y;
            sum3z += group3[j].z;
        }
        
        center1.x = double(sum1x/group1.size());
        center1.y = double(sum1y/group1.size());
        center1.z = double(sum1z/group1.size());
        center2.x = double(sum2x/group2.size());
        center2.y = double(sum2y/group2.size());
        center2.z = double(sum2z/group2.size());
        center3.x = double(sum3x/group3.size());
        center3.y = double(sum3y/group3.size());
        center3.z = double(sum3z/group3.size());
        printf("banana x y z = %f, %f, %f, \n",center1.x,center1.y,center1.z);
        
        printf("apple x y z = %f, %f, %f, \n",center2.x,center2.y,center2.z);
        
        printf("grape x y z = %f, %f, %f, \n",center3.x,center3.y,center3.z);
        
        count ++;
        
        if(count ==1000)
        {
            break;
        }
        
    }
    
    for(int i=1; i<20; i++)
    {
        std::stringstream image_name;
        image_name << RANDOM << "/images-" << i << ".jpg";
        image = cv::imread(image_name.str(), IMREAD_COLOR);
        cv::cvtColor(image, imageCopy, COLOR_BGR2HSV);
        
        int count =0;
        double sumH = 0;
        double sumS = 0;
        double sumV = 0;
        for(int i=0; i<image.rows ; i ++)
        {
            for(int j=0 ; j<image.cols ; j++)
            {
                if(imageCopy.at<uchar>(i,j) == 255)
                    continue;
                
                int img_h = imageCopy.at<Vec3b>(i,j)[0];
                int img_s = imageCopy.at<Vec3b>(i,j)[1];
                int img_v = imageCopy.at<Vec3b>(i,j)[2];
                
                
                count ++;
                sumH += img_h;
                sumS += img_s;
                sumV += img_v;
            }
        }
        
        tmp.x = (double)(sumH/count);
        tmp.y = (double)(sumS/count);
        tmp.z = (double)(sumV/count);
        
        tem_distance1 = sqrt(pow(center1.x-tmp.x, 2)+pow(center1.y-tmp.y, 2)+pow(center1.z-tmp.z, 2));
        tem_distance2 = sqrt(pow(center2.x-tmp.x, 2)+pow(center2.y-tmp.y, 2)+pow(center2.z-tmp.z, 2));
        tem_distance3 = sqrt(pow(center3.x-tmp.x, 2)+pow(center3.y-tmp.y, 2)+pow(center3.z-tmp.z, 2));
        
        double min = ((tem_distance1>tem_distance2)?tem_distance2:tem_distance1)>tem_distance3 ? tem_distance3:((tem_distance1>tem_distance2)?tem_distance2:tem_distance1) ;
        
        cv::namedWindow("input");
        cv::moveWindow("input", 200, 200);
        cv::namedWindow("output");
        cv::moveWindow("output", 1000, 200 );
        
        if(min == tem_distance1)
        {
            min = tem_distance1;
            printf("grape! \n");
            
            cv::imshow("output",image_Grape);
            cv::imshow("input", image);
            cv::waitKey(0);
            
        }
        
        else if(min == tem_distance2)
        {
            min = tem_distance2;
            printf("banana! \n");
            
            cv::imshow("output",image_Banana);
            cv::imshow("input", image);
            cv::waitKey(0);
        }
        else
        {
            min = tem_distance3;
            printf("apple! \n");
            
            cv::imshow("output",image_Apple);
            cv::imshow("input", image);
            cv::waitKey(0);
            
        }
        cv::destroyAllWindows();
    }
}





