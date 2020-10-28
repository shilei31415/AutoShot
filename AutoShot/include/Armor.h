//
// Created by shilei on 19-12-25.
//

#ifndef HEROVISION_ARMOR_H
#define HEROVISION_ARMOR_H

#include "Mark.h"

class Armor {
public:
    Armor();
    Armor(Mark mk1,Mark mk2,int id);
    void show(cv::Mat &frame);
    void getImage(cv::Mat &frame,cv::Mat &boundingImage);
    void getname(char name[]);

    cv::Point3f poision;
    cv::Point2f center;
    float score;
    int id;

    std::vector<cv::Point2f> concors;

    /*
    *   ///////////////////////////////////
    *   //                               //
    *   //  1                            //   4
    * // //                             // //
    * // //                             // //
    * // //                             // //
    * // //                             // //
    * // // 2                           // //  3
    *   //                               //
    *   //                               //
    *   ///////////////////////////////////
    */
    cv::Rect ROI;

private:
    char name[5];
};

#endif //HEROVISION_ARMOR_H
