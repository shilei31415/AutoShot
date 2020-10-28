RoboMaster2020赛季我参与了英雄视觉代码的编写
串口及识别为疫情前编写,可正确通信,及识别
疫情后,在录制的视频基础上进行少量修改,提高了运行速率,并没有实际运行的效果

文件目录如下:

```
   AutoShot								
    ├── AutoShot							//识别装甲
    │   ├── include							//.h文件
    │   │   ├── ANN.h						//数字识别
    │   │   ├── Armor.h						//Mark匹配
    │   │   ├── Mark.h						//识别Mark
    │   │   ├── pnp.h						//PnP测距
    │   │   ├── TargetFind.h				//调用Armor和Mark
    │   │   └── trajectory.h				//考虑空气阻力的抛物线(未使用)
    │   └── src								//.cpp文件
    │       ├── ANN.cpp
    │       ├── Armor.cpp
    │       ├── Mark.cpp
    │       ├── pnp.cpp
    │       ├── TargetFind.cpp
    │       └── targetFinderTest.cpp		//测试targetFinder
    ├── CMakeLists.txt
    ├── HeroVision.h						//常用宏定义
    ├── include.h							//常用头文件
    ├── main.cpp
    ├── others								//其他功能
    │   ├── Calibrator						//标定
    │   │   ├── Calibrate.cpp
    │   │   ├── Calibrator.cpp
    │   │   ├── Calibrator.h
    │   │   ├── cr
    │   │   └── ip
    │   ├── camera							//相机驱动
    │   │   ├── CameraApi.h
    │   │   ├── CameraDefine.h
    │   │   ├── CameraStatus.h
    │   │   ├── MindVisionCamera.cpp
    │   │   └── MindVisionCamera.h
    │   ├── JLink							//自己编写的调试助手,显示变量随时间的变化
    │   │   ├── JLink.cpp
    │   │   └── JLink.h
    │   ├── picture							//程序运行时保存的图片
    │   ├── SerialPort						//串口通信
    │   │   ├── SerialPort.cpp
    │   │   ├── SerialPort.h
    │   │   ├── SerialPortTest.cpp
    │   │   └── serial.sh
    │   └── video							//程序运行时保存的视频
    ├── README.md
    └── tools								//运行及调试时常用函数
        ├── excption						//catch excption并保存到txt (未使用)
        │   ├── myExcption.cpp
        │   └── myExcption.h
        ├── MathTool						//常用数学函数
        │   └── MathTool.h
        ├── setter							//读取参数
        │   ├── model.pb
        │   ├── para.yaml
        │   ├── setter.cpp
        │   └── setter.h
        └── time							//计算帧率,控制帧率
            ├── timer.cpp
            └── timer.h
```


算法原理与讲解请参考 https://shilei31415.github.io/RM.html
参考队友王海龙编写了串口通信, 参考队友邱添编写了标定
本程序还有许多不完善,希望下一赛季可以得到进一步完善
