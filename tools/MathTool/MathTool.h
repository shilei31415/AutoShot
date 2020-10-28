//
// Created by shilei on 19-12-26.
//

#ifndef HEROVISION_MATHTOOL_H
#define HEROVISION_MATHTOOL_H

#include <opencv2/opencv.hpp>

inline float p2pDis(cv::Point2f pt1,cv::Point2f pt2)
{
    return sqrtf(pow((pt1.x-pt2.x),2)+pow((pt1.y-pt2.y),2));
}

inline cv::Scalar At(cv::Mat &frame,int i,int j)
{
    uchar *data=frame.ptr<uchar>(i);
    cv::Scalar color;
    color[0]=data[3*j];
    color[1]=data[3*j+1];
    color[2]=data[3*j+2];
    return color;
}

inline cv::Scalar At(cv::Mat &frame,cv::Point pt1)
{
    int i=pt1.y,j=pt1.x;
    uchar *data=frame.ptr<uchar>(i);
    cv::Scalar color;
    color[0]=data[3*j];
    color[1]=data[3*j+1];
    color[2]=data[3*j+2];
    return color;
}

#endif //HEROVISION_MATHTOOL_H
