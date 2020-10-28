//
// Created by shilei on 20-1-4.
//

#ifndef HEROVISION2_ANN_H
#define HEROVISION2_ANN_H

#include "../../HeroVision.h"
#include "Armor.h"
#include "../../tools/setter/setter.h"

class ANN {
public:
    std::string model_path;
    bool isLoad;

    ANN(setter& set);
    int forword(cv::Mat &input);
    void getID(Armor &armor,cv::Mat &frame);


private:
    cv::dnn::Net net;
    int ID[15]={0,1,2,3,4,5,7,8,10,20,30,40,50,70,80};
};


#endif //HEROVISION2_ANN_H
