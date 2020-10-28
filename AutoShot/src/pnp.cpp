//
// Created by shilei on 19-12-28.
//

#include "include/pnp.h"

pnp::pnp() {}

pnp::pnp(setter set) {
    this->CameraMatrix=set.CameraMatrix;
    this->DistCoeffs=set.DistCoeffs;

    NormalRealPoint.push_back(cv::Point3f(-0.5*set.NormalArmorWidth,0.5*set.NormalArmorHeight,0));
    NormalRealPoint.push_back(cv::Point3f(-0.5*set.NormalArmorWidth,-0.5*set.NormalArmorHeight,0));
    NormalRealPoint.push_back(cv::Point3f(0.5*set.NormalArmorWidth,-0.5*set.NormalArmorHeight,0));
    NormalRealPoint.push_back(cv::Point3f(0.5*set.NormalArmorWidth,0.5*set.NormalArmorHeight,0));

    LargeRealPoint.push_back(cv::Point3f(-0.5*set.LargerArmorWidth,0.5*set.LargerArmorHeight,0));
    LargeRealPoint.push_back(cv::Point3f(-0.5*set.LargerArmorWidth,-0.5*set.LargerArmorHeight,0));
    LargeRealPoint.push_back(cv::Point3f(0.5*set.LargerArmorWidth,-0.5*set.LargerArmorHeight,0));
    LargeRealPoint.push_back(cv::Point3f(0.5*set.LargerArmorWidth,0.5*set.LargerArmorHeight,0));
    rvec=cv::Mat_<double>(3,1);
    tvec=cv::Mat_<double>(3,1);
}

void pnp::slove(Armor &armor) {

    if(armor.id>=10)
        cv::solvePnP(LargeRealPoint,armor.concors,
                  CameraMatrix,DistCoeffs,
                  rvec,tvec,false,cv::SOLVEPNP_AP3P);
    else
        cv::solvePnP(NormalRealPoint,armor.concors,
                     CameraMatrix,DistCoeffs,
                     rvec,tvec,false,cv::SOLVEPNP_AP3P);

    armor.poision.x=tvec.at<double>(0);
    armor.poision.y=tvec.at<double>(1);
    armor.poision.z=tvec.at<double>(2);
}
