//
// Created by shilei on 19-12-25.
//

#include "SerialPort.h"
#include "../../tools/excption/myExcption.h"

int main()
{
    SerialPort STM32("/dev/SerialPort");
    SerialPort::Rxpackage rec;
    while(1)
    {
        STM32.readBuffer2(rec);

    }

    return 0;
}