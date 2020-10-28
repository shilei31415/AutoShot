//
// Created by shilei on 19-12-28.
//

#ifndef HEROVISION_TIMER_H
#define HEROVISION_TIMER_H

#include "../../HeroVision.h"

inline std::string getTimePictureC() {
    time_t TimeValue;
    time (&TimeValue);
    char tmp[64];
    strftime(tmp, sizeof(tmp), "../others/video/%Y-%m-%d_%H_%M_%S.avi",localtime(&TimeValue));
    return tmp;
}

class timer {
private:
    double start,finish;
    int numT=0;    //运行周期
public:
    timer();
    std::string showTime();
    void showOnImage(cv::Mat image);
    void update();
    void clear();
    //double time;
};


#endif //HEROVISION_TIMER_H
