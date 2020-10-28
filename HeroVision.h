//
// Created by shilei on 19-12-26.
//

#ifndef HEROVISION_HEROVISION_H
#define HEROVISION_HEROVISION_H

#include <opencv2/opencv.hpp>
#include <iostream>
#include <cmath>
#include <math.h>
#include "tools/excption/myExcption.h"
#include <string>

#define R cv::Scalar(0,0,255)               //red
#define G cv::Scalar(0,255,0)               //green
#define B cv::Scalar(255,0,0)               //blue
#define Y cv::Scalar(0,255,255)             //yellow
#define C cv::Scalar(255,255,0)             //cyan青色
#define P cv::Scalar(255,0,255)             //purple
#define W cv::Scalar(255,255,255)           //white
#define D cv::Scalar(0,0,0)                 //dark

#define Debug(x)                            std::cout<<"Debug"<<x<<std::endl;
#define Debug2(s1,s2)                       std::cout<<"Debug: "<<s1<<'\t'<<s2<<std::endl;
#define Debug3(message,position,image)      cv::        //将message放到image的position行
#define Debug4(x)                           std::cout<<(#x)<<": "<<x<<std::endl;

//Calculate the time consumed by the step x
#define dtime(x)     static double time=0;\
                    static int num=0;\
                    double time0 = static_cast<double>(cv::getTickCount());\
                    x\
                    time0=((double)cv::getTickCount()-time0)/cv::getTickFrequency();\
                    time+=time0;\
                    num++;\
                    if(num%1==0){\
                        std::cout<<(#x)<<' '<<time*1000<<"ms"<<std::endl;\
                        time=0;\
                    }

#define sint short int
#define  Contours std::vector<std::vector<cv::Point>>

#endif //HEROVISION_HEROVISION_H
