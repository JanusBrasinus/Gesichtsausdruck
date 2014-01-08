//
//  GUI.h
//  Preset
//
//  Created by Janis Brusius on 07.01.14.
//  Copyright (c) 2014 Janis Brusius. All rights reserved.
//

#ifndef Preset_GUI_h
#define Preset_GUI_h

#include "findFace.h"


class GUI {
    
public:
    GUI();
    ~GUI(void);
    
    void processUserFrame(const cv::Mat& videoFrame,const cv::Point& eyePos,const cv::Point& mouthPos,int eyeWidth,int eyeHeight,int mouthWidth,int mouthHeight);
    cv::Mat getUserFrame();
    
    
    
private:
    
    
    
    cv::Mat userFrame;
    cv::Scalar eyeColor;
    cv::Scalar mouthColor;

};


#endif


