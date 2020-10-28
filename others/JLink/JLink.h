//
// Created by shilei on 20-1-12.
//

#ifndef HEROVISION3_JLINK_H
#define HEROVISION3_JLINK_H

#include <iostream>
#include <vector>
#include <opencv2/opencv.hpp>
#include <time.h>

class JLink {
public:
    JLink(float num);//比例
    void print(double data,std::string variable);
    void show();

private:
    std::vector<std::vector<cv::Point2f>> datas;
    std::vector<std::string> variables;
    std::vector<cv::Scalar> colors;
    cv::Mat windows;
    float bili=1000.0;
};


#endif //HEROVISION3_JLINK_H
