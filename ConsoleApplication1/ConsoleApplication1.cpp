#include <iostream>
#include <cstdio>
#include <Opencv2/opencv.hpp>
#include <string.h>
#include <Number.h>
#include <Guns.h>
using namespace cv;
using namespace std;

void test_matchTemplate()
{
    Mat src, templ, dst, Test,Test1;
    // TM_SQDIFF是平方差匹配、TM_SQDIFF_NORMED是标准平方差匹配。
    // 利用平方差来进行匹配，最好匹配为0。匹配越差，匹配值越大。
    int Method = cv::TemplateMatchModes::TM_SQDIFF_NORMED;
    int Max_track = 5;
    int x = 8;
    src = imread("Resources/Compare/2.bmp"); // 待检测图片
    templ = imread("Resources/Default/6/19.bmp"); // 模板图片
    Test = imread("Resources/Numbers/315.bmp");

    // 初始化结果图
    int width = src.cols - templ.cols + 1;
    int height = src.rows - templ.rows + 1;
    Mat result(width, height, CV_32FC1);
    
    // 匹配
    matchTemplate(src, templ, result, Method, Mat());
    //normalize(result, result, 1, 0, NORM_MINMAX, -1, Mat());
    Point minLoc, maxLoc;
    double min, max;
    Point temLoc;
    minMaxLoc(result, &min, &max, &minLoc, &maxLoc, Mat());
    // 根据匹配结果确定最佳的位置，不同的方法对应的最佳位置不同，例如 TM_SQDIFF 像素值最小（黑色）的地方对应最佳的位置
    if (Method == cv::TemplateMatchModes::TM_SQDIFF || Method == cv::TemplateMatchModes::TM_SQDIFF_NORMED) {
        temLoc = minLoc;
        cout << "可信度 = " << min <<"(越接近0越好)\n";
        if (Method == cv::TemplateMatchModes::TM_SQDIFF_NORMED && min > 0.1) {
            cout << "识别错误 \n" ;
        }
    }
    else {
        temLoc = maxLoc;
        if (Method == cv::TemplateMatchModes::TM_CCORR) {
            cout << "可信度 = " << max << "(完全匹配会得到很大值，不匹配会得到一个很小值或0)\n";
        }
        if (Method == cv::TemplateMatchModes::TM_CCORR_NORMED) {
            cout << "可信度 = " << max << "(完全匹配会得到1， 完全不匹配会得到0)\n";
        }
        if (Method == cv::TemplateMatchModes::TM_CCOEFF) {
            cout << "可信度 = " << max << "(完全匹配会得到一个很大值，完全不匹配会得到0，完全负相关会得到很大的负数)\n";
        }
        if (Method == cv::TemplateMatchModes::TM_CCOEFF_NORMED) {
            cout << "可信度 = " << max << "(完全匹配会得到1，完全负相关匹配会得到-1，完全不匹配会得到0)\n";
        }
    }
    
    // 绘制矩形
    src.copyTo(dst);
    rectangle(dst, cv::Rect(temLoc.x, temLoc.y, templ.cols, templ.rows), cv::Scalar(0, 0, 255), 2, 8);
    //rectangle(result, cv::Rect(temLoc.x, temLoc.y, templ.cols, templ.rows), cv::Scalar(0, 0, 255), 2, 8);
    //imshow("output", result);
    cout << "x = " << temLoc.x << " y = " << temLoc.y << endl;

    imshow("Test", Test);
    imshow("src", src);
    imshow("templ", templ);
    imshow("match", dst);

    Mat Rio;
    Rect rect(temLoc.x+60, temLoc.y,65,46);
    Rio = src(rect);
    Mat result1(width, height, CV_32FC1);
    int width1 = Rio.cols - Test.cols + 1;
    int height1 = Rio.rows - Test.rows + 1;
    matchTemplate(src, templ, result1, Method, Mat());
    Point minLoc1, maxLoc1;
    double min1, max1;
    Point temLoc1;
    minMaxLoc(result1, &min1, &max1, &minLoc1, &maxLoc1, Mat());
    if (Method == cv::TemplateMatchModes::TM_SQDIFF || Method == cv::TemplateMatchModes::TM_SQDIFF_NORMED) {
        temLoc1 = minLoc1;
        cout << "可信度 = " << min1 << "(越接近0越好)\n";
        /*/if (Method == cv::TemplateMatchModes::TM_SQDIFF_NORMED && min1 > 0.1) {
            cout << "识别错误 \n";
        }*/
    }
    // 绘制矩形
    Rio.copyTo(Test1);
    rectangle(Test1, cv::Rect(temLoc1.x, temLoc1.y, Test.cols, Test.rows), cv::Scalar(0, 0, 255), 2, 8);


    imshow("RECT", Rio);
    
    
    imshow("match1", Test1);
   // printf("wtpal %d", Method);
    
}

int main()
{
    // 模板匹配
    test_matchTemplate();
    waitKey(0);
    //destroyAllWindows();
    //return 0;
}