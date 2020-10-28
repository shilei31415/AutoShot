//
// Created by shilei on 19-12-25.
//

#include "../../include.h"
int main()
{
    try {

        timer timer1;
        MindVisionCamera camera;
        camera.SetExposureTime(3);
        camera.SetResolution(cv::Size(1280,1024));  //set ROI 3ms
        TargetFind finder(g_setter);
        char name[10];
        static double time=0;
        static int number=0;
        cv::Mat frame;                              //create a mat 0.3-0.4ms
        while(1)
        {
//            double time0= static_cast<double>(cv::getTickCount());
            camera>>frame;                          //9ms (1280,1024)  2ms(640,480)
//            time0=((double)cv::getTickCount()-time0)/cv::getTickFrequency();
//            time+=time0;
//            number++;
//            if(number==1000)
//                std::cout<<time<<std::endl;

            std::vector<Armor> armors=finder.findArmor(frame);
//            frame*=10;
//            sprintf(name,"%d",i++);
//            std::string nam="../others/picture/"+std::string(name)+".png";
//            cv::imwrite(nam,frame);
            timer1.showOnImage(frame);

            cv::imshow("xiaoguo",frame);
            cv::waitKey(1);

        }
    }
    catch (myExcption &e)
    {
        std::cout<<e.message;
    }
    catch (cv::Exception &e)
    {
        std::cout<<e.msg<<std::endl;
    }
}
