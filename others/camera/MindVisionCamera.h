//
// Created by roggie on 19-11-4.
//

#ifndef ALLIANCE2020_CV_GROUP_MINDVISIONCAMERA_H
#define ALLIANCE2020_CV_GROUP_MINDVISIONCAMERA_H

#include "CameraApi.h"
#include <opencv2/opencv.hpp>

class MindVisionCamera:public cv::VideoCapture
{
private:
    tSdkCameraDevInfo tCameraEnumList;
    tSdkCameraCapbility tCapability;      //设备描述信息
    tSdkImageResolution tImageResolution;
    tSdkFrameHead sFrameInfo;
    bool isRecord;
    bool isMindVisionCamera;
public:
    unsigned char *g_pRgbBuffer;
    int h_camera;

    /*
     * MindVision 工业相机初始化
     */
    MindVisionCamera();

    /*
     * 普通USB相机初始化
     */
    MindVisionCamera(int cam);

    /*
     * 载入视频方式初始化
     */
    MindVisionCamera(std::string input_file);

    /*
     * 工业相机反初始化
     * VideoCapture析构
     */
    ~MindVisionCamera();

    /*
     * 设置曝光时间
     */
    void SetExposureTime(double fExposureTime);
/*
     * 设置读取分辨率
     */
    cv::Size ReadResolution();

    /*
     * 设置ROI
     */
    void SetResolution(cv::Size tImageResolution, cv::Size offset = cv::Size(0, 0));

    /*
     * 读取一张图像，重载了>> 操作符
     * 说明：在VideoCapture中 >> 操作 已被vitual实现，此函数重写了 >>
     */
    cv::VideoCapture &operator >> (cv::Mat &frame);


};


#endif //ALLIANCE2020_CV_GROUP_MINDVISIONCAMERA_H
