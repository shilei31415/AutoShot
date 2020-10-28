//
// Created by shilei on 19-12-25.
//

#include <include/Armor.h>

#include "../include/Armor.h"

Armor::Armor() {}

//左、右灯条
Armor::Armor(Mark mk1, Mark mk2,int id) {
    this->id=id;
    if(mk1.center.x>mk2.center.x)
        std::swap(mk1,mk2);
    concors.push_back(mk1.pointTop);
    concors.push_back(mk1.pointDown);
    concors.push_back(mk2.pointDown);
    concors.push_back(mk2.pointTop);
    center=(concors[0]+concors[1]+concors[2]+concors[3])*0.25;
    //用装甲板面积初始化score
    cv::Point2f pt12=concors[0]-concors[1],
                pt23=concors[1]-concors[2],
                pt34=concors[2]-concors[3],
                pt41=concors[3]-concors[0];
    score=(fabs(pt12.x*pt23.y-pt12.y*pt23.x)+fabs(pt34.x*pt41.y-pt34.y*pt41.x))*0.5;
    name[4]=id;
    if(id>=10)
        name[1]='L',id=id/10;
    else name[1]='S';
    name[0]='0'+id;
    name[2]=0;
}

void Armor::show(cv::Mat &frame) {
    name[4]=id;
    if(id>=10)
        name[1]='L',id=id/10;
    else name[1]='S';
    name[0]='0'+id;
    name[2]=0;
    cv::circle(frame,center,10,G,2);
    cv::line(frame,concors[0],concors[2],C,2);
    cv::line(frame,concors[1],concors[3],C,2);
    char data[20];
    sprintf(data,"%d %d %d",(int)poision.x,(int)poision.y,(int)poision.z);

    cv::putText(frame,data,center+cv::Point2f(0,20),cv::FONT_HERSHEY_COMPLEX,0.7,Y,2,0);
    cv::putText(frame,name,center+cv::Point2f(0,-20),cv::FONT_HERSHEY_COMPLEX,1.0,C,2,0);
}

void Armor::getImage(cv::Mat &frame, cv::Mat &boundingImage) {
    cv::Rect rect=cv::boundingRect(concors);
    cv::Point br=rect.br(),tl=rect.tl();
    br.y=rect.br().y+rect.size().height/3;
    tl.y=rect.tl().y-rect.size().height/3;
    if(br.y>(frame.rows-1))br.y=frame.rows-1;
    if(br.x>(frame.cols-1))br.x=frame.cols-1;
    if(br.x<0)br.x=0;
    if(br.y<0)br.y=0;
    if(tl.y>(frame.rows-1))tl.y=frame.rows-1;
    if(tl.x>(frame.cols-1))tl.x=frame.cols-1;
    if(tl.x<0)tl.x=0;
    if(tl.y<0)tl.y=0;
    cv::Rect rec(br,tl);
    boundingImage=frame(rec).clone();
    boundingImage*=10;
}
