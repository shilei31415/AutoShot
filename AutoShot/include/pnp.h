//
// Created by shilei on 19-12-28.
//

#ifndef HEROVISION_PNP_H
#define HEROVISION_PNP_H


#include "Armor.h"
#include "../../tools/setter/setter.h"

class pnp {
public:
    cv::Mat rvec;
    cv::Mat tvec;
    cv::Mat_<float> CameraMatrix;
    cv::Mat DistCoeffs;
    std::vector<cv::Point3f> LargeRealPoint;
    std::vector<cv::Point3f> NormalRealPoint;

    pnp();
    pnp(setter set);
    void slove(Armor &armor);
};


#endif //HEROVISION_PNP_H
