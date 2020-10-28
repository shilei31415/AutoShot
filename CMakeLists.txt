cmake_minimum_required(VERSION 3.5)
project(HeroVision)

set( CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11 -march=native -O3 -pthread" )
link_libraries(/lib/libMVSDK.so)
include_directories(AutoShot)
include_directories(others/camera)
include_directories(others/Calibrator)
include_directories(tools/excption)
include_directories(Military_Module)

find_package(OpenCV)

add_executable(HeroVision main.cpp
        HeroVision.h
        others/camera/MindVisionCamera.cpp  others/camera/MindVisionCamera.h
        AutoShot/src/Mark.cpp               AutoShot/include/Mark.h
        AutoShot/src/Armor.cpp              AutoShot/include/Armor.h
        AutoShot/include/robot.h
        AutoShot/src/TargetFind.cpp         AutoShot/include/TargetFind.h
        AutoShot/include/trajectory.h
        others/SerialPort/SerialPort.cpp    others/SerialPort/SerialPort.h
        tools/excption/myExcption.cpp       tools/excption/myExcption.h
        tools/MathTool/MathTool.h           include.h
        tools/setter/setter.cpp             tools/setter/setter.h
        AutoShot/src/pnp.cpp                AutoShot/include/pnp.h
        tools/time/timer.cpp                tools/time/timer.h AutoShot/src/ANN.cpp AutoShot/include/ANN.h)
target_link_libraries(HeroVision ${OpenCV_LIBS})

add_executable(targetFinderTest AutoShot/src/targetFinderTest.cpp
        HeroVision.h
        AutoShot/src/Mark.cpp               AutoShot/include/Mark.h
        AutoShot/src/Armor.cpp              AutoShot/include/Armor.h
        AutoShot/include/robot.h
        AutoShot/src/TargetFind.cpp         AutoShot/include/TargetFind.h
        AutoShot/include/trajectory.h
        others/camera/MindVisionCamera.cpp  others/camera/MindVisionCamera.h
        tools/excption/myExcption.cpp       tools/excption/myExcption.h
        tools/MathTool/MathTool.h           include.h
        tools/setter/setter.cpp             tools/setter/setter.h
        AutoShot/src/pnp.cpp                AutoShot/include/pnp.h
        tools/time/timer.cpp                tools/time/timer.h AutoShot/src/ANN.cpp AutoShot/include/ANN.h)
target_link_libraries(targetFinderTest ${OpenCV_LIBS})

add_executable(Calibrator others/Calibrator/Calibrate.cpp
        others/Calibrator/Calibrator.cpp    others/Calibrator/Calibrator.h
        tools/setter/setter.cpp             tools/setter/setter.h
        others/camera/MindVisionCamera.cpp  others/camera/MindVisionCamera.h
        tools/excption/myExcption.cpp       tools/excption/myExcption.h)
target_link_libraries(Calibrator ${OpenCV_LIBS})

add_executable(SerialPortTest others/SerialPort/SerialPortTest.cpp
        HeroVision.h
        others/SerialPort/SerialPort.cpp    others/SerialPort/SerialPort.h
        tools/excption/myExcption.cpp       tools/excption/myExcption.h
        tools/setter/setter.cpp             tools/setter/setter.h)
target_link_libraries(SerialPortTest ${OpenCV_LIBS})