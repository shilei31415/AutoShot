RoboMaster2020赛季我参与了英雄视觉代码的编写
串口及识别为疫情前编写,可正确通信,及识别
疫情后,在录制的视频基础上进行少量修改,提高了运行速率,并没有实际运行的效果

文件目录如下:
'''
   AutoShot
    ├── AutoShot
    │   ├── include
    │   │   ├── ANN.h
    │   │   ├── Armor.h
    │   │   ├── Mark.h
    │   │   ├── pnp.h
    │   │   ├── robot.h
    │   │   ├── TargetFind.h
    │   │   └── trajectory.h
    │   └── src
    │       ├── ANN.cpp
    │       ├── Armor.cpp
    │       ├── Mark.cpp
    │       ├── pnp.cpp
    │       ├── TargetFind.cpp
    │       └── targetFinderTest.cpp
    ├── CMakeLists.txt
    ├── HeroVision.h
    ├── include.h
    ├── main.cpp
    ├── others
    │   ├── Calibrator
    │   │   ├── Calibrate.cpp
    │   │   ├── Calibrator.cpp
    │   │   ├── Calibrator.h
    │   │   ├── cr
    │   │   └── ip
    │   ├── camera
    │   │   ├── CameraApi.h
    │   │   ├── CameraDefine.h
    │   │   ├── CameraStatus.h
    │   │   ├── MindVisionCamera.cpp
    │   │   └── MindVisionCamera.h
    │   ├── JLink
    │   │   ├── JLink.cpp
    │   │   └── JLink.h
    │   ├── picture
    │   ├── SerialPort
    │   │   ├── SerialPort.cpp
    │   │   ├── SerialPort.h
    │   │   ├── SerialPortTest.cpp
    │   │   └── serial.sh
    │   └── video
    ├── README.md
    └── tools
        ├── excption
        │   ├── myExcption.cpp
        │   └── myExcption.h
        ├── MathTool
        │   └── MathTool.h
        ├── setter
        │   ├── model.pb
        │   ├── para.yaml
        │   ├── setter.cpp
        │   └── setter.h
        └── time
            ├── timer.cpp
            └── timer.h
'''


算法原理与讲解请参考 https://shilei31415.github.io/RM.html
