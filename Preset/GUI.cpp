#include <opencv2/objdetect/objdetect.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>

#include <iostream>
#include <stdio.h>
#include <algorithm>

#include "GUI.h"
#include "findFace.h"



GUI::GUI()

{
    eyeColor = (0,255,0);
    mouthColor = (0,0,255);
}

GUI::~GUI(void){
}

void GUI::processUserFrame(const cv::Mat& videoFrame,const cv::Point& eyePos,const cv::Point& mouthPos,int eyeWidth,int eyeHeight,int mouthWidth,int mouthHeight){

    videoFrame.copyTo(userFrame);

    ellipse( userFrame, eyePos, cv::Size( eyeWidth*0.4, eyeHeight*0.5), 0, 0, 360, eyeColor, 4, 8, 0 );
    ellipse( userFrame, mouthPos, cv::Size( mouthWidth*0.4, mouthHeight*0.5), 0, 0, 360, mouthColor, 4, 8, 0 );
   
}

cv::Mat GUI::getUserFrame(){

    return userFrame;
}



