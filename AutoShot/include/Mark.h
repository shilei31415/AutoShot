//
// Created by shilei on 19-12-25.
//

#ifndef HEROVISION_MARK_H
#define HEROVISION_MARK_H

#include "../../HeroVision.h"
#include "../../tools/MathTool/MathTool.h"
#define RED 1
#define BLUE 0
#define other 3
#define matched 1
#define unmatch 0

class Mark :public cv::RotatedRect{
public:
    char color;
    bool isMatch;
    cv::Point2f pointTop,pointDown;
    float size;

    Mark();
    Mark(cv::RotatedRect &rRect);
    Mark(cv::RotatedRect &rRect,char color);
    void show(cv::Mat &frame);
};

float Dis4Mark(Mark mk1,Mark mk2);
float malposition(Mark mk1,Mark mk2);

#endif //HEROVISION_MARK_H
