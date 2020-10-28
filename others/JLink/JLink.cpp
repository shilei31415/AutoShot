//
// Created by shilei on 20-1-12.
//

#include <../HeroVision.h>
#include "JLink.h"

cv::RNG rng(12356);
JLink::JLink(float num) {
    windows=cv::Mat::zeros(1000,1500,CV_8UC3);
    bili=1000.0*num;
    cv::namedWindow("JLink",cv::WINDOW_NORMAL);
    cv::resizeWindow("JLink",cv::Size(1500,1000));
}

void JLink::print(double data, std::string variable) {
    bool isFind=false;
    for(int i=0;i<variables.size();i++)
        if(variable==variables[i])
        {
            datas[i].push_back(cv::Point2f(clock()/bili,data));
            isFind=true;
        }
    if(isFind==false)
    {
        variables.push_back(variable);
        datas.push_back(std::vector<cv::Point2f>());
        datas[datas.size()-1].push_back(cv::Point2f(clock()/bili,data));
        colors.push_back(cv::Scalar(rng.uniform(0,255),rng.uniform(0,255),rng.uniform(0,255)));
    }
    show();
}

void JLink::show() {
    float max=clock()/bili;
    float min=datas[0][0].x;
    for(int i=1;i<datas.size();i++)
    {
        if(datas[i][0].x<min)
            min=datas[i][0].x;
    }
    if(max-min>1400)
    {
        min=max-1400;
        windows=cv::Mat::zeros(1000,1500,CV_8UC3);
    }
    //Debug3(min)
    //Debug3(max)
    for(int i=0;i<datas.size();i++)
    {
        for(int j=0;j<datas[i].size();j++)
            cv::circle(windows,datas[i][j]-cv::Point2f(min,-500),2,colors[i],-1);
    }

    cv::imshow("JLink",windows);
    cv::waitKey(1);
}

