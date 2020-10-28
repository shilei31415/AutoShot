//
// Created by shilei on 19-12-25.
//

#include "SerialPort.h"

SerialPort::SerialPort(const char *dev_name) {
    Debug2("serialID",dev_name)
    fd=open(dev_name,O_RDWR | O_NOCTTY | O_NDELAY);
    if(fd==-1)
        throw myExcption("串口打开失败",error_SerialPort);
    fcntl(fd,F_SETFL,0);                                    //查看文件状态
    struct termios port_settings;
    cfmakeraw(&port_settings);                            //设置为原始模式,所有输入都按字节处理,实测没有这步配置,FF有时会读成7F甚至5F
    cfsetispeed(&port_settings, B115200);                 //输入波特率
    cfsetospeed(&port_settings, B115200);                 //输出波特率
    //设置数据流控制
    port_settings.c_cflag &= ~PARENB;                     //允许输出产生奇偶信息以及输入的奇偶校验（启用同位产生与侦测）
    port_settings.c_cflag &= ~CSTOPB;                     //
    port_settings.c_cflag &= ~CSIZE;
    port_settings.c_cflag |= CS8;
    port_settings.c_cflag |=(CLOCAL | CREAD);             //保证程序不会占用串口,使得能够从串口中读取输入数据
    tcsetattr(fd, TCSANOW, &port_settings);
    txpackage.pitch=0;
    txpackage.yaw=0;
}

//bool SerialPort::readBuffer(SerialPort::Rxpackage &tempRx) {
//    unsigned char r_buf[sizeof(Rxpackage)];
//    int n=read(fd,r_buf, sizeof(Rxpackage));
//    if(n==-1||r_buf[0]!=0xFF||r_buf[sizeof(Rxpackage)-1]!=0xFE)
//        return false;
//    sint *t_ptr=(sint*)(r_buf+1);
//    tempRx.pitch    =t_ptr[0]/(100.0f);
//    tempRx.yaw      =t_ptr[1]/(100.0f);
//    tempRx.V_pitch  =t_ptr[2]/(100.0f);
//    tempRx.V_yaw    =t_ptr[3]/(100.0f);
//    tempRx.V_x      =t_ptr[4]/(100.0f);
//    tempRx.V_y      =t_ptr[5]/(100.0f);
//    tempRx.flag     =r_buf[13];
//    showRead(tempRx);
//    return true;
//}

bool SerialPort::writeBuffer(SerialPort::Txpackage &tempTx) {
    unsigned char t_buf[sizeof(tempTx)];
    sint* t_ptr=(sint*)(t_buf+1);
    t_ptr[0]=tempTx.pitch*100;
    t_ptr[1]=tempTx.yaw*100;
    t_buf[0]=0xFF;
    t_buf[5]=tempTx.flag;
    t_buf[6]=0xFE;
    int n=write(fd,t_buf,7);
    if(n==-1)
        return false;
    return true;
}

void SerialPort::closeSerial() {
    close(fd);
}

//void SerialPort::showRead(SerialPort::Rxpackage &tempRx) {
//    std::cout<<"Recieve:";
//    for(int i=0;i< sizeof(tempRx);i++)
//        printf("%02X ",((char*)(&tempRx))[i]);
//    std::cout<<std::endl;
//    std::cout<<tempRx.yaw<<'\t'<<tempRx.pitch<<
//             '\t'<<tempRx.V_yaw<<'\t'<<tempRx.V_pitch<<
//             '\t'<<tempRx.V_x<<'\t'<<tempRx.V_y<<std::endl;
//}

void SerialPort::showWrite(SerialPort::Txpackage &tempTx) {
    std::cout<<"send:";
    for(int i=0;i< sizeof(tempTx);i++)
        printf("%02X ",((char*)(&tempTx))[i]);
    std::cout<<std::endl;
    std::cout<<tempTx.pitch<<'\t'<<tempTx.yaw<<'\t'<<tempTx.flag<<std::endl;
}

bool SerialPort::readBuffer2(SerialPort::Rxpackage &tempRx) {
    unsigned char r_buf[sizeof(Rxpackage)];
    //Debug4(sizeof(Rxpackage))
    read(fd,r_buf, sizeof(Rxpackage));
//    for(int i=0;i< sizeof(tempRx);i++)
//        printf("%02X ",((char*)(&tempRx))[i]);
//    std::cout<<std::endl;
    sint * t_ptr = (sint *)(r_buf+1);
    tempRx.pitch=t_ptr[0]/(100.0f);
    tempRx.yaw=t_ptr[1]/(100.0f);
//    Debug4(tempRx.yaw)
//    Debug4(tempRx.pitch);
//    Debug('\n')
    return false;
}
