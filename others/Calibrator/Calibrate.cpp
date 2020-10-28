//
// Created by shilei on 19-12-26.
//

#include "Calibrator.h"
#include "../../include.h"

int main()
{
    Debug("标定")
    try {
        MindVisionCamera camera;
        camera.SetExposureTime(30);
        camera.SetResolution(cv::Size(1280, 1024));
        Calibrator cal(g_setter, camera);
    }
    catch (myExcption &e)
    {
        std::cout<<e.message;
    }
}