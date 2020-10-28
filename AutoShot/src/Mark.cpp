//
// Created by shilei on 19-12-25.
//

#include "../include/Mark.h"

Mark::Mark() {}

Mark::Mark(cv::RotatedRect &rRect) {
    this->center=rRect.center;
    cv::Point2f vertex[4];
    rRect.points(vertex);
    if(p2pDis(vertex[0],vertex[1])<p2pDis(vertex[1],vertex[2]))
    {
        pointTop=(vertex[0]+vertex[1])/2;
        pointDown=(vertex[2]+vertex[3])/2;
    }
    else
    {
        pointTop=(vertex[0]+vertex[3])/2;
        pointDown=(vertex[1]+vertex[2])/2;
    }
    size=p2pDis(pointTop,pointDown);
    if(pointTop.y>pointDown.y)
        std::swap(pointDown,pointTop);

    pointTop+=cv::Point2f(0,-2);
    pointDown+=cv::Point2f(0,2);

    if(rRect.size.height>rRect.size.width)
        angle=(rRect.angle+90);
    else
        angle=(rRect.angle);
    if(angle<0)
        angle+=180;
    isMatch=unmatch;
}

Mark::Mark(cv::RotatedRect &rRect, char color) {
    this->color=color;
    this->center=rRect.center;
    cv::Point2f vertex[4];
    rRect.points(vertex);
    if(p2pDis(vertex[0],vertex[1])<p2pDis(vertex[1],vertex[2]))
    {
        pointTop=(vertex[0]+vertex[1])/2;
        pointDown=(vertex[2]+vertex[3])/2;
    }
    else
    {
        pointTop=(vertex[0]+vertex[3])/2;
        pointDown=(vertex[1]+vertex[2])/2;
    }
    size=p2pDis(pointTop,pointDown);
    if(pointTop.y>pointDown.y)
        std::swap(pointDown,pointTop);

    pointTop+=cv::Point2f(0,-2);
    pointDown+=cv::Point2f(0,2);

    if(rRect.size.height>rRect.size.width)
        angle=(rRect.angle+90);
    else
        angle=(rRect.angle);
    if(angle<0)
        angle+=180;
    isMatch=unmatch;
}

void Mark::show(cv::Mat &frame) {
    cv::circle(frame,pointTop,1,R,-1);
    cv::circle(frame,pointDown,1,G,-1);
    char data[50];
    sprintf(data,"%d %d",int(size),int(angle));
    cv::putText(frame,data,pointTop+cv::Point2f(10,-10),cv::FONT_HERSHEY_COMPLEX,0.7,Y,2,0);
}

float Dis4Mark(Mark mk1, Mark mk2) {
    return p2pDis(mk1.center,mk2.center);
}

float malposition(Mark mk1, Mark mk2) {
    cv::Point2f axis=((mk1.pointTop+mk2.pointTop)-(mk1.pointDown+mk2.pointDown))*0.5;
    cv::Point2f dis=(mk1.center-mk2.center);
    float mo=sqrtf(dis.x*dis.x+dis.y+dis.y)*sqrtf(axis.x*axis.x+axis.y*axis.y);
    return fabsf(axis.dot(dis))/mo;
}
