//
// Created by shilei on 19-12-25.
//

#ifndef HEROVISION_ROBOT_H
#define HEROVISION_ROBOT_H

#include "Armor.h"
#define V cv::Point3f

class robot {
public:
    std::vector<Armor> Armors;
private:
    //敌方机器人移动速度
    V V4robot;
    //地方机器人自转角速度
    float oumiga;
};


#endif //HEROVISION_ROBOT_H
