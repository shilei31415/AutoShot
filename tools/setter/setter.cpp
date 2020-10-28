//
// Created by shilei on 19-12-26.
//

#include <opencv2/core/persistence.hpp>
#include "setter.h"

setter::setter() {
    cv::FileStorage settingFile;
    assert(settingFile.open("../tools/setter/para.yaml",cv::FileStorage::READ));

    settingFile["whoIam"]>>whoIam;
    //---------------------------------------------------Mark
    settingFile["para4Boxfilter"]>>para4Boxfilter;
    settingFile["threshold"]>>threshold;
    settingFile["threshold4BR"]>>threshold4BR;
    settingFile["threshold4RB"]>>threshold4RB;
    settingFile["threshold4BG"]>>threshold4BG;
    settingFile["threshold4RG"]>>threshold4RG;
    settingFile["blueRate"]>>blueRate;
    settingFile["redRate"]>>redRate;
    settingFile["minContourSize"]>>minContourSize;
    settingFile["maxRatioLW"]>>maxRatioLW;
    settingFile["minRatioLW"]>>minRatioLW;
    settingFile["minAngle"]>>minAngle;
    settingFile["maxAngle"]>>maxAngle;

    //----------------------------------------------------Armor
    settingFile["maxRatio42Mark"]>>maxRatio42Mark;
    settingFile["dAngle"]>>dAngle;
    settingFile["maxMalposition"]>>maxMalposition;
    settingFile["dis4small"]>>dis4small;
    settingFile["dis4big"]>>dis4big;

    //----------------------------------------------------pnp
    settingFile["camera_Matrix"]>>CameraMatrix;
    settingFile["dist_Coeffs"]>>DistCoeffs;
    settingFile["NormalArmorWidth"]>>NormalArmorWidth;
    settingFile["NormalArmorHeight"]>>NormalArmorHeight;
    settingFile["LargerArmorWidth"]>>LargerArmorWidth;
    settingFile["LargerArmorHeight"]>>LargerArmorHeight;

    //-----------------------------------------------------ANN
    settingFile["model_path"]>>model_path;

    //----------------------------------------------------SerialPort
    settingFile["devname"]>>devname;

    //-----------------------------------------------------Calibrate
    settingFile["CalibrationResultPath"]>>CalibrationResultPath;
    settingFile["CalibrationPointPath"]>>CalibrationPointPath;
    settingFile["SAVE_IMAGE_PATH"]>>SAVE_IMAGE_PATH;
    settingFile["CornersMatrix"]>>CornersMatrix;
    settingFile["Rectangle"]>>Rectangle;
}