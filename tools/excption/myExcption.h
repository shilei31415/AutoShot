//
// Created by shilei on 19-12-26.
//

#ifndef HEROVISION_MYEXCPTION_H
#define HEROVISION_MYEXCPTION_H

#define error_SerialPort 0
#define fail_link_camera 1

#include <string>

class myExcption {
public:
    std::string message;
    int error_ID;

    myExcption(std::string,int id);
};


#endif //HEROVISION_MYEXCPTION_H
