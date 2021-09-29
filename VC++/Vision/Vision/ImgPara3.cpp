#include "pch.h"
#include "ImgPara3.h"

bool ImgPara3::LoadFromFile(char* path)
{
    std::ifstream is(path);
    if (is.is_open())
    {
        is >> minAreaLeft;
        is >> maxAreaLeft;
        is >> minAreaRight;
        is >> maxAreaRight;
        is.close();
        return true;
    }
    return false;
}

bool ImgPara3::SaveToFile(char* path)
{
    std::ofstream os(path);

    os << minAreaLeft << "\n" 
        << maxAreaLeft << "\n" 
        << minAreaRight << "\n" 
        << maxAreaRight;
    os.close();
    return true;
}

bool ImgPara3::ImgProcessing(cv::Mat& src, cv::Mat& dst)
{
    src.copyTo(dst);
    cv::Mat image;
    cv::cvtColor(src, image, cv::COLOR_BGR2GRAY);
    cv::threshold(image, image, 128, 255, cv::THRESH_BINARY);
    cv::GaussianBlur(image, image, cv::Size(5, 5), 3, 3);
    cv::Canny(image, image, 100, 200, 3, false);

    std::vector<cv::Vec3f> circles;
    cv::HoughCircles(image, circles, cv::HOUGH_GRADIENT, 2, image.cols / 10);

    if (circles.size() != 2)
    {
        TRACE("计算圆失败!\n");
        return false;
    }
    bool result = false;


    double area = 0.0;
    if (circles[0][0] < circles[1][0])
    {
        //circles[0]为左圆
        area = CV_PI * circles[0][2] * circles[0][2];
        if (area > maxAreaLeft || area < minAreaLeft)
        {
            TRACE("左圆面积不合要求!\n");
            //return false;
        }
        area = CV_PI * circles[1][2] * circles[1][2];
        if (area > maxAreaRight || area < minAreaRight)
        {
            TRACE("右圆面积不合要求!\n");
            //return false;
        }
    }
    else
    {
        //circles[0]为右圆
        area = CV_PI * circles[1][2] * circles[1][2];
        if (area > maxAreaLeft || area < minAreaLeft)
        {
            TRACE("左圆面积不合要求!\n");
            //return false;
        }
        area = CV_PI * circles[0][2] * circles[0][2];
        if (area > maxAreaRight || area < minAreaRight)
        {
            TRACE("右圆面积不合要求!\n");
            //return false;
        }
    }

    for (size_t i = 0; i < 2; ++i) {
        cv::circle(dst,
            cv::Point(cvRound(circles[i][0]), cvRound(circles[i][1])),
            cvRound(circles[i][2]),
            cv::Scalar(0, 255, 0),
            1,
            cv::LINE_AA);
    }
    return true;
}
