RoboMaster2020赛季我参与了英雄视觉代码的编写
串口及识别为疫情前编写,可正确通信,及识别
疫情后,在录制的视频基础上进行少量修改,提高了运行速率,并没有实际运行的效果

文件目录如下:

├── README.md                   // help
├── main.cpp                    //主函数
├── HeroVision                  //常用宏定义
├── CMakeLists.txt
├── include.h					//常用头文件
├── AutoShot                    //装甲板的识别及自动瞄准
│   ├── include                 //.h文件
│   │   ├── ANN.h				//神经网络,数字识别相关部分
│   │   ├── Armor.h				//装甲板的识别,主要包括Mark的匹配算法
│   │   ├── Mark.h				//Mark的识别
│   │   ├── pnp.h				//PnP测距
│   │   ├── TargetFind.h		//调用Mark和Armor
│   │   ├── tarjectory.h		//考虑空气阻力的弹道计算(未完成)
│   ├── src						//.cpp文件
│   │   ├── ANN.cpp				
│   │   ├── Armor.cpp				
│   │   ├── Mark.cpp			
│   │   ├── pnp.cpp			
│   │   ├── TargetFind.cpp		
│   │   ├── tarjectory.cpp
│   │   ├── TargetFindTest.cpp	//测试TargetFind
├── others                    	//其他功能
│   ├── Calibrator              //标定
│   ├── camera					//相机驱动
│   ├── JLink					//输出变量随时间的变化情况
│   ├── picture					//程序运行中保存的图片
│   ├── SerialPort				//串口通信
│   ├── video					//程序运行中保存的视频
├── tools						//调试,运行时常用函数
│   ├── excption				//修改excption,希望将程序运行过程中的excption保存,并未使用
│   ├── MathTool				//常用数学函数
│   ├── setter					//读取参数,节约调试时间
│   ├── time					//计算帧率,限制帧率

算法原理与讲解请参考 https://shilei31415.github.io/RM.html
