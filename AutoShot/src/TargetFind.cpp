//
// Created by shilei on 19-12-25.
//

#include <cmath>
#include <include/TargetFind.h>

#include "../include/TargetFind.h"
#include "../../others/SerialPort/SerialPort.h"

TargetFind::TargetFind() {}

TargetFind::TargetFind(setter &set) {
    this->whoIam=set.whoIam;

    this->threshold=set.threshold;
    this->para4Boxfilter=set.para4Boxfilter;
    this->dis4big=set.dis4big;
    this->dis4small=set.dis4small;
    this->maxMalposition=set.maxMalposition;
    this->dAngle=set.dAngle;
    this->maxRatio42Mark=set.maxRatio42Mark;
    this->maxAngle=set.maxAngle;
    this->minAngle=set.minAngle;
    this->maxRatioLW=set.maxRatioLW;
    this->minContourSize=set.minContourSize;
    this->redRate=set.redRate;
    this->blueRate=set.blueRate;
    this->threshold4BR=set.threshold4BR;
    this->minRatioLW=set.minRatioLW;
    this->threshold4BG=set.threshold4BG;
    this->threshold4RB=set.threshold4RB;
    this->threshold4RG=set.threshold4RG;
}

Contours TargetFind::getContours(cv::Mat &frame) {
    cv::Mat tempImage=frame.clone();
    std::vector<std::vector<cv::Point>> contours;
    cv::Size kSize(para4Boxfilter*2+1,para4Boxfilter*2+1);

    cv::blur(frame,tempImage,kSize);
    cv::cvtColor(tempImage,tempImage,cv::COLOR_BGR2GRAY);
    tempImage=tempImage>threshold;
    cv::findContours(tempImage,contours,cv::RETR_EXTERNAL,cv::CHAIN_APPROX_NONE);
    cv::drawContours(tempImage,contours,-1,D);
    contours.clear();

    //cv::imshow("gray",tempImage);
    cv::findContours(tempImage,contours,cv::RETR_EXTERNAL,cv::CHAIN_APPROX_NONE);
    return contours;
}

Contours TargetFind::getContours2(cv::Mat &frame) {
    cv::Mat tempImage=frame.clone();
    std::vector<std::vector<cv::Point>> contours;

    cv::cvtColor(tempImage,tempImage,cv::COLOR_BGR2GRAY);
    tempImage=tempImage>threshold;
    cv::findContours(tempImage,contours,cv::RETR_EXTERNAL,cv::CHAIN_APPROX_NONE);
    return contours;
}

Contours TargetFind::getContours3(cv::Mat &frame){
    cv::Mat tempImage=frame.clone();
    std::vector<std::vector<cv::Point>> contours;
    cv::Size kSize(para4Boxfilter*2+1,para4Boxfilter*2+1);

    cv::blur(frame,tempImage,kSize);
    if(whoIam==BLUE) {
        for (int i = 0; i < tempImage.rows; i++) {
            uchar *data = tempImage.ptr<uchar>(i);
            for (int j = 0; j < tempImage.cols; j++) {
                if(data[j*3+2]-data[j*3]>30)
                    data[j*3]=255,data[j*3+1]=255,data[j*3+2]=255;
                else data[j*3]=0,data[j*3+1]=0,data[j*3+2]=0;
            }
        }
    }
    if(whoIam==RED) {
        for (int i = 0; i < tempImage.rows; i++) {
            uchar *data = tempImage.ptr<uchar>(i);
            for (int j = 0; j < tempImage.cols; j++) {
                if(data[j*3]-data[j*3+2]>30)
                    data[j*3]=255,data[j*3+1]=255,data[j*3+2]=255;
                else data[j*3]=0,data[j*3+1]=0,data[j*3+2]=0;
            }
        }
    }
    cv::cvtColor(tempImage,tempImage,cv::COLOR_BGR2GRAY);
    cv::findContours(tempImage,contours,cv::RETR_EXTERNAL,cv::CHAIN_APPROX_NONE);
    cv::drawContours(tempImage,contours,-1,D);
    contours.clear();

    //cv::imshow("gray",tempImage);
    cv::findContours(tempImage,contours,cv::RETR_EXTERNAL,cv::CHAIN_APPROX_NONE);
    return contours;
}

std::vector<Mark> TargetFind::findMark(cv::Mat &frame) {
    Contours contours=getContours3(frame);

    std::vector<Mark> marks;
    for(int i=0;i<contours.size();i++) {
        cv::RotatedRect rRect=cv::minAreaRect(contours[i]);
        if(contours[i].size()>minContourSize)
            if(MIN(rRect.size.width,rRect.size.height)*maxRatioLW>MAX(rRect.size.width,rRect.size.height))
                //if(MIN(rRect.size.width,rRect.size.height)*minRatioLW<MAX(rRect.size.width,rRect.size.height))
                {
                    Mark mk(rRect);
                    if(mk.angle>maxAngle||mk.angle<minAngle)
                        continue;
                    marks.push_back(mk);
                    //mk.show(frame);
                }
    }
    return marks;
}

std::vector<Armor> TargetFind::findArmor(cv::Mat &frame,SerialPort::Rxpackage &rec,ANN &ann,cv::Mat &trans) {
    std::vector<Mark> marks=findMark(frame);
    std::vector<Armor> Armors;
    for(int i=0;i<marks.size();i++)
        for(int j=i+1;j<marks.size();j++)
        {
            if(MAX(marks[i].size,marks[j].size)/MIN(marks[i].size,marks[j].size)<maxRatio42Mark)
            if(abs(marks[i].angle-marks[j].angle)<=dAngle)
            if(malposition(marks[i],marks[j])<maxMalposition)
            if(fabs(marks[i].center.y-marks[j].center.y)<MIN(marks[i].size,marks[j].size))
            {
                if (Dis4Mark(marks[i], marks[j]) < dis4small * (marks[i].size + marks[j].size) * 0.5)
                {
                    Armor armor(marks[i], marks[j], 1);

                    ann.getID(armor, frame);
                    if(armor.id==0)
                        continue;

                    slover.slove(armor);
                    //armor.score=malposition(marks[i],marks[j]);
//                    float x=armor.poision.x,y=armor.poision.y+50,z=armor.poision.z+80;
//                    armor.poision.x=-x*sin(rec.yaw)+y*sin(rec.pitch)*cos(rec.yaw)+z*cos(rec.pitch)*cos(rec.yaw);
//                    armor.poision.y=x*cos(rec.yaw)+y*sin(rec.pitch)*sin(rec.yaw)+z*cos(rec.pitch)*sin(rec.yaw);
//                    armor.poision.z=y*(-cos(rec.pitch))+z*sin(rec.pitch);

                    cv::Mat pos=(cv::Mat_<float>(3,1)<< armor.poision.x,
                                                        armor.poision.y,
                                                        armor.poision.z);
                    pos=trans*pos;
                    armor.poision.x=pos.at<float>(0);
                    armor.poision.y=pos.at<float>(1);
                    armor.poision.z=pos.at<float>(2);

                    armor.show(frame);
                    Armors.push_back(armor);
                }
//                if(Dis4Mark(marks[i], marks[j]) >= dis4small * (marks[i].size + marks[j].size) * 0.5)
//                    if(Dis4Mark(marks[i], marks[j]) < dis4big * (marks[i].size + marks[j].size) * 0.5)
//                    {
//                        Armor armor(marks[i], marks[j], 10);
//                        //armor.score=malposition(marks[i],marks[j]);
//                        ann.getID(armor, frame);
//                        if(armor.id==0)
//                            continue;
//
//                        slover.slove(armor);
////                        cv::projectPoints(slover.LargeRealPoint,slover.rvec,slover.tvec,
////                                slover.CameraMatrix,slover.DistCoeffs,armor.concors);
//
//                        cv::Mat pos=(cv::Mat_<float>(3,1)<< armor.poision.x,
//                                                            armor.poision.y,
//                                                            armor.poision.z);
//                        pos=trans*pos;
//                        armor.poision.x=pos.at<float>(0);
//                        armor.poision.y=pos.at<float>(1);
//                        armor.poision.z=pos.at<float>(2);
//
//                        //armor.show(frame);
//                        Armors.push_back(armor);
//                    }
            }
        }
//        int theMax=0;
//    for(int i=0;i<Armors.size();i++)
//        if(Armors[i].score>Armors[theMax].score)
//            theMax=i;
//    if(Armors.size()>0)
//        Armors[theMax].show(frame);
    return Armors;
}

Armor TargetFind::target(std::vector<Armor> Armors) {
    int theMax=0;
    for(int i=0;i<Armors.size();i++)
        if(Armors[i].score>Armors[theMax].score)
            theMax=i;
        return Armors[theMax];
}
