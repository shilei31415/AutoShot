//
// Created by shilei on 19-12-25.
//

#ifndef HEROVISION_TARGETFIND_H
#define HEROVISION_TARGETFIND_H

#include "../../HeroVision.h"
#include "Mark.h"
#include "Armor.h"
#include "robot.h"
#include "../../tools/setter/setter.h"
#include "../../include.h"
#include <include/ANN.h>
#include "../../others/SerialPort/SerialPort.h"

class TargetFind {
public:
    int whoIam;
    //Mark
    int para4Boxfilter=2;
    int threshold=15;
    int threshold4BR=10;
    int threshold4RB=10;
    int threshold4BG=20;
    int threshold4RG=20;
    float blueRate=0.6;
    float redRate=0.6;
    int minContourSize=20;
    float maxRatioLW=8;
    float minRatioLW=1.2;
    int minAngle=70;
    int maxAngle=120;
    //Armor
    float maxRatio42Mark=1.5;
    int dAngle=10;
    float maxMalposition=0.3;
    float dis4small=2.8;
    float dis4big=4.7;

    TargetFind();
    TargetFind(setter &set);
    Contours getContours(cv::Mat &frame);
    Contours getContours2(cv::Mat &frame);
    Contours getContours3(cv::Mat &frame);
    std::vector<Mark> findMark(cv::Mat &frame);
    std::vector<Armor> findArmor(cv::Mat &frame,SerialPort::Rxpackage &rec,ANN &ann,cv::Mat &trans);
    Armor target(std::vector<Armor> Armors);

    std::vector<robot> findRobot(cv::Mat &frame);

};



#endif //HEROVISION_TARGETFIND_H
