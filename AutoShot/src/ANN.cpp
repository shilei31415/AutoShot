//
// Created by shilei on 20-1-4.
//

#include "include/ANN.h"

ANN::ANN(setter &set) {
    this->model_path=set.model_path;
    net=cv::dnn::readNetFromTensorflow(model_path);
    if(net.empty())
        isLoad= false;
    else{
        for(int i=0;i<net.getLayerNames().size();i++)
            std::cout<<net.getLayerNames()[i]<<"  ";
        std::cout<<"successfuly load ANN"<<std::endl;
        isLoad=true;
    }
}

int ANN::forword(cv::Mat &input) {
    if(isLoad==false)
        return -1;

    if(input.channels()>1)
        cv::cvtColor(input,input,cv::COLOR_BGR2GRAY);
    cv::resize(input,input,cv::Size(48,36));
    input=input.reshape(0,1728);
    input.convertTo(input,CV_32FC3);
    input=input/255.0;
    input=cv::dnn::blobFromImage(input,1.0,cv::Size(1,1728));

    net.setInput(input,"image");
    cv::Mat pred=net.forward("result");

    float *row=pred.ptr<float>(0);
    int max=0;
    for(int i=0;i<pred.cols;i++)
    {
        if(row[i]>row[max])
            max=i;
    }
    if(row[max]>0.7)
        return max;
    else return max;
}

void ANN::getID(Armor &armor, cv::Mat &frame) {
    static int i=1;
    char name[100];
    if(isLoad) {
        cv::Mat input;
        armor.getImage(frame, input);
        //cv::imshow("input",input);
        sprintf(name,"%d.png",i++);
        //cv::imwrite(name,input);
        int pred = forword(input);
        //std::cout<<pred<<std::endl;
        armor.id=ID[pred];
    }
}