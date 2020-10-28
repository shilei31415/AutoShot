//
// Created by roggie on 19-11-4.
//

#include "MindVisionCamera.h"
#include <CameraDefine.h>
#include "../../HeroVision.h"

MindVisionCamera::MindVisionCamera() : isRecord(false)
{
    isMindVisionCamera = true;
    std::cout << "------[2]" << "CameraInit------" << std::endl;

    int camera_counts = 1;
    int status = CameraEnumerateDevice(&tCameraEnumList, &camera_counts);
    if (status)
    {
        std::cerr << "camera enum fail,error code=" << status << " :\nNo device." << std::endl;
        if(status==-16)
            throw myExcption("摄像头连接失败",fail_link_camera);
        return;
    }
    if (!camera_counts)
    {
        std::cerr << "camera_disconnect" << std::endl;
        return;
    }
    status = CameraInit(&tCameraEnumList, -1, -1, &h_camera);
    if (status)
    {
        std::cerr << "camera init fail" << std::endl;
        return;
    }
    CameraGetCapability(h_camera, &tCapability);
    CameraSetIspOutFormat(h_camera, CAMERA_MEDIA_TYPE_BGR8);
    CameraSetAeState(h_camera, FALSE);
    CameraSetFrameSpeed(h_camera, 1);
    g_pRgbBuffer = (unsigned char *) malloc(
            tCapability.sResolutionRange.iHeightMax * tCapability.sResolutionRange.iWidthMax * 3);
    CameraGetImageResolution(h_camera, &tImageResolution);
    CameraPlay(h_camera);
}

MindVisionCamera::MindVisionCamera(int cam) : cv::VideoCapture(cam)
{
    isMindVisionCamera = false;
}

MindVisionCamera::~MindVisionCamera()
{
    CameraUnInit(h_camera);
    free(g_pRgbBuffer);
    VideoCapture::release();
}

MindVisionCamera::MindVisionCamera(std::string input_file) : cv::VideoCapture(input_file)
{
    std::cout << "[2]Local Video Init:----";
    isMindVisionCamera = false;
    if (this->VideoCapture::isOpened())
        std::cout << "Succeed" << std::endl;
    else
        std::cerr << "Fail" << std::endl;
}

void MindVisionCamera::SetResolution(cv::Size roi, cv::Size offset )
{
    tImageResolution.iIndex = 0xff;
    tImageResolution.iWidth = roi.width;
    tImageResolution.iHeight = roi.height;
    tImageResolution.iWidthFOV = roi.width;
    tImageResolution.iHeightFOV = roi.height;
    tImageResolution.iHOffsetFOV = ((1280 - roi.width) / 2) + offset.width;
    tImageResolution.iVOffsetFOV = ((1024 - roi.height) / 2) + offset.height;
    CameraSetMirror(h_camera,1,true);
    CameraSetMirror(h_camera,0,true);
    CameraSetImageResolution(h_camera, &tImageResolution);
}

void MindVisionCamera::SetExposureTime(double ExposureTime_ms)
{
    CameraSetExposureTime(h_camera, ExposureTime_ms * 1000);
}

cv::VideoCapture &MindVisionCamera::operator>>(cv::Mat &frame)
{
    static VideoCapture *v1;
    if (isMindVisionCamera == 0)
    {
        this->cv::VideoCapture::read(frame);
        cv::imshow("mid",frame);
        return *v1;
    }
    BYTE *pbyBuffer;
    if (CameraGetImageBuffer(h_camera, &sFrameInfo, &pbyBuffer, 1000) == CAMERA_STATUS_SUCCESS)
    {
        CameraImageProcess(h_camera, pbyBuffer, g_pRgbBuffer, &sFrameInfo);
        CameraReleaseImageBuffer(h_camera, pbyBuffer);
        frame = cv::Mat(tImageResolution.iHeight, tImageResolution.iWidth, CV_8UC3, g_pRgbBuffer);
        return *v1;
    }
    else
        frame.release();
    return *v1;
}

cv::Size MindVisionCamera::ReadResolution() {
    return cv::Size(tImageResolution.iWidth,tImageResolution.iHeight);
}
