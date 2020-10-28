//
// Created by shilei on 19-12-26.
//

#ifndef HEROVISION_SETTER_H
#define HEROVISION_SETTER_H

#include "../../HeroVision.h"

//Who am i
//Blue : 1
//Red :0

class setter {
public:
    int whoIam;
//-------------------findtarget--------------
//------------Mark--------------
    int para4Boxfilter;
    int threshold;
    int threshold4BR;
    int threshold4RB;
    int threshold4BG;
    int threshold4RG;
    float blueRate;
    float redRate;
    int minContourSize;
    float maxRatioLW;
    float minRatioLW;
    int minAngle;
    int maxAngle;
//------------Armor--------------
    float maxRatio42Mark;
    int dAngle;
    float maxMalposition;
    float dis4small;
    float dis4big;
//---------------pnp--------------
    cv::Mat CameraMatrix;
    cv::Mat DistCoeffs;
    float NormalArmorWidth;
    float NormalArmorHeight;
    float LargerArmorWidth;
    float LargerArmorHeight;
//--------------ANN--------------
    std::string model_path;


//-----------SerialPort----------
    std::string devname;


//----------Calibrate-----------
    std::string SAVE_IMAGE_PATH;
    cv::Size CornersMatrix;
    cv::Size Rectangle;
    std::string CalibrationResultPath;
    std::string CalibrationPointPath;

    setter();
};



#endif //HEROVISION_SETTER_H
