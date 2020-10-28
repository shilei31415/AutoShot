//
// Created by shilei on 19-12-25.
//

#ifndef HEROVISION_SERIALPORT_H
#define HEROVISION_SERIALPORT_H

#include <string>
#include <unistd.h>
#include <fcntl.h>
#include <termios.h>
#include "../../HeroVision.h"

class SerialPort {
public:
    struct Txpackage                     //float 4字节 char 1字节 int 4字节
    {
        char   frameHead=0xFF;
        float   pitch=0;
        float   yaw=0;
        char   flag;
        char   frameTail=0xFE;
    };
    struct Rxpackage
    {
        char    frameHead=0xFF;
        float   pitch;
        float   yaw;
        char   bigBuffFlag=0;
        char   bulletSpeed;

        float V_pitch;
        float V_yaw;
        char  rotateFlag;
//        float   V_pitch;
//        float   V_yaw;
//        float   V_x;
//        float   V_y;
//        char    flag;
        char   frameTail=0xFE;
    };
    int fd;

    Rxpackage rxpackage;
    Txpackage txpackage;

    SerialPort(const char *dev_name);
    void closeSerial();
    bool readBuffer(Rxpackage &tempRx);
    bool readBuffer2(Rxpackage &tempRx);
    bool writeBuffer(Txpackage &tempTx);
    bool writeBuffer2(Txpackage &tempTx);   //将发送数据三次方

    void showRead(Rxpackage &tempRx);
    void showWrite(Txpackage &tempTx);
};


#endif //HEROVISION_SERIALPORT_H
