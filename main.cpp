//
// Created by shilei on 19-12-25.
//

#include "../../include.h"
#include "others/SerialPort/SerialPort.h"
#include <thread>

cv::Mat pic;
//SerialPort STM32("/dev/SerialPort");
//
//void readserialport(SerialPort::Rxpackage &rec)
//{
//    while(1) {
//        STM32.readBuffer2(rec);
//        rec.pitch=rec.pitch*CV_PI/180.0;
//        rec.yaw=rec.yaw*CV_PI/180.0;
////        Debug4(rec.pitch)
////        Debug4(rec.yaw)
//    }
//}

void imageDeal(SerialPort::Rxpackage &rec)
{
    cv::KalmanFilter kf(3,3);
    cv::Mat state(3,1,CV_32F);
    cv::Mat processNoise(3,1,CV_32F);
    cv::Mat measurement=cv::Mat::zeros(3,1,CV_32F);
    kf.transitionMatrix=(cv::Mat_<float>(3,3)<< 1,0,0,
                                                0,1,0,
                                                0,0,1);
    cv::setIdentity(kf.measurementMatrix);
    cv::setIdentity(kf.processNoiseCov,cv::Scalar::all(1e-5));
    cv::setIdentity(kf.measurementNoiseCov,cv::Scalar::all(2e-5));
    cv::setIdentity(kf.errorCovPost);

    timer timer1;
    MindVisionCamera camera("/home/shilei/Desktop/AVI/test3.avi");
    camera.SetExposureTime(3);
//    camera.SetResolution(cv::Size(1280,1024));  //set ROI 3ms
    TargetFind finder(g_setter);
    ANN ann(g_setter);
    cv::Mat frame;
    Armor target;
    std::vector<cv::Point3f> points;
    while(1)
    {
//  计算摄像头坐标系到绝对坐标系的转换关系
        cv::Mat trans=(cv::Mat_<float>(3,3)<<   -sin(rec.yaw),  sin(rec.pitch)*cos(rec.yaw),cos(rec.pitch)*cos(rec.yaw),
                                                cos(rec.yaw),   sin(rec.pitch)*sin(rec.yaw),cos(rec.pitch)*sin(rec.yaw),
                                                    0,          -cos(rec.pitch),            sin(rec.pitch));
        cv::Mat snart;
//   计算绝对坐标系到摄像头坐标系的转换关系 逆矩阵
        cv::invert(trans,snart);
        camera>>frame;
        if(!frame.data)
        {
            std::cout<<"finish"<<std::endl;
            return;
        }
        std::vector<Armor> armors=finder.findArmor(frame,rec,ann,trans);
        if(armors.size()!=0)
        {
            target=finder.target(armors);
            measurement.at<float>(0)=target.poision.x;
            measurement.at<float>(1)=target.poision.y;
            measurement.at<float>(2)=target.poision.z;
            kf.correct(measurement);
            cv::Mat prediction=kf.predict();
            target.poision.x=prediction.at<float>(0);
            target.poision.y=prediction.at<float>(1);
            target.poision.z=prediction.at<float>(2);

            measurement.at<float>(0)=target.poision.x;
            measurement.at<float>(1)=target.poision.y;
            measurement.at<float>(2)=target.poision.z;
            kf.correct(measurement);
            prediction=kf.predict();
            target.poision.x=prediction.at<float>(0);
            target.poision.y=prediction.at<float>(1);
            target.poision.z=prediction.at<float>(2);
            target.show(frame);

            points.push_back(target.poision);
            if(points.size()>=10)
            {
//                for(int i=0;i<10;i++)
//                    std::cout<<points[i]<<" ";
//                std::cout<<std::endl;
//          计算速度
                cv::Point3f v=(points[9]-points[0])*70/40;
//          预测
                cv::Point3f next=target.poision+v*0.3;
                cv::Mat pos=(cv::Mat_<float>(3,1)<< next.x,
                                                    next.y,
                                                    next.z);
//          绝对坐标系转为像素
                pos=slover.CameraMatrix*(snart*pos);
                pos/=pos.at<float>(2);
                cv::Point nextTarget;
                nextTarget.x=pos.at<float>(0),nextTarget.y=pos.at<float>(1);
                cv::circle(frame,nextTarget,10,R,10);
                //std::cout<<pos<<std::endl;
                //std::cout<<sqrtf(v.x*v.x+v.y*v.y+v.z*v.z)<<std::endl;
                points.erase(points.begin());

//                STM32.txpackage.pitch=(512-nextTarget.y)/20.0;
//                STM32.txpackage.yaw=(nextTarget.x-40-640)/40.0;
//                STM32.txpackage.flag=4;
//                STM32.writeBuffer(STM32.txpackage);

            }

        }
        timer1.showOnImage(frame);
        frame.copyTo(pic);

        pic *= 15;
        cv::imshow("result", pic);
        cv::waitKey(1);
    }
}

void show()
{
    while(1) {
        //Debug4(frame.data)
        if (pic.data) {
            pic *= 15;
            cv::imshow("xiaoguo", pic);
        }
        cv::waitKey(1);
    }
}

int main()
{
    SerialPort::Rxpackage rec;
    //std::thread read(readserialport,std::ref(rec));
    std::thread image(imageDeal,std::ref(rec));
//    std::thread showImage(show);

    image.join();
//    read.join();
//    showImage.join();
    return 0;
}
