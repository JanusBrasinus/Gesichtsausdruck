#include <opencv2/objdetect/objdetect.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>

#include <iostream>
#include <stdio.h>
#include <algorithm>

#include "processMidiData.h"



processMidiData::processMidiData()

{

}

processMidiData::~processMidiData(void){}



int processMidiData::processEyeData(cv::Mat eyeFrame){

    eyeTracked = eyeTracking(eyeFrame);
    eyeHigh = 0;
    eyeLow = 0;

    
    for(int i = 0; i < eyeTracked.cols; i++){
        for(int j = eyeTracked.rows/3; j < eyeTracked.rows/3*2; j++){
            
            if(j < eyeTracked.rows/2 && eyeTracked.at<uchar>(j,i) == 0)
            {
                eyeHigh++;
            }
            if(j > eyeTracked.rows/2 && eyeTracked.at<uchar>(j,i) == 0)
            {
                eyeLow++;
            }
            
        }
    
    }
    
    if(eyeHigh > eyeLow){
        
        return 1;

        
    }
    else{
        
        return 2;

    
    }
  

}

int processMidiData::processMouthData(cv::Mat mouthFrame){
    
    mouthTracked = mouthTracking(mouthFrame);
    mouthHL = 0;
    mouthHR = 0;
    mouthLL = 0;
    mouthLR = 0;
    
    for(int i = 0; i < mouthTracked.cols; i++){
        for(int j = 0; j < mouthTracked.rows; j++){
            
            if(j < mouthTracked.rows/2 && i < mouthTracked.cols/2 && mouthTracked.at<uchar>(j,i) == 255)
            {
                mouthHL++;
            }
            if(j < mouthTracked.rows/2 && i > mouthTracked.cols/2 && mouthTracked.at<uchar>(j,i) == 255)
            {
                mouthHR++;
            }
            if(j > mouthTracked.rows/2 && i < mouthTracked.cols/2 && mouthTracked.at<uchar>(j,i) == 255)
            {
                mouthLL++;
            }
            if(j > mouthTracked.rows/2 && i > mouthTracked.cols/2 && mouthTracked.at<uchar>(j,i) == 255)
            {
                mouthLR++;
            }
            
        }
        
    }
    
    if(mouthHL > mouthHR && mouthHL > mouthLL && mouthHL > mouthLR){
        
        return 1;
        
        
    }
    if(mouthHR > mouthHL && mouthHR > mouthLL && mouthHR > mouthLR){
        
        return 2;
        
        
    }
    if(mouthLL > mouthHL && mouthLL > mouthHR && mouthLL > mouthLR){
        
        return 3;
        
        
    }
    
    else{
        
        return 4;
        
    }
    
    
}


cv::Mat processMidiData::eyeTracking(cv::Mat eyeFrame){
    
    cvtColor(eyeFrame, eyeFrameHSV,CV_BGR2HSV);
    split(eyeFrameHSV, eyePlanes);
    // Schwellwertbildung Hue für den Mund
    //inRange(eyePlanes[0], 10, 100, eyePlanes[0]);
    // Schwellwertbildung Saturation für das linke Auge
    threshold(eyePlanes[1], eyePlanes[1], 10, 255, cv::THRESH_BINARY);
    // SchwellenwetBildung Value für das linke Auge
    threshold(eyePlanes[2], eyePlanes[2], 30, 255, cv::THRESH_BINARY);
    // Kombination aller Masken
    multiply(eyePlanes[2], eyePlanes[1], eyePlanes[2]);
    //multiply(eyePlanes[0], eyePlanes[2], eyePlanes[0]);
    
    return eyePlanes[2];
    
}


cv::Mat processMidiData::mouthTracking(cv::Mat mouthFrame){
    
    cvtColor(mouthFrame, mouthFrameHSV,CV_BGR2HSV);
    split(mouthFrameHSV, mouthPlanes);
    // Schwellwertbildung Hue für den Mund
    inRange(mouthPlanes[0], 10, 100, mouthPlanes[0]);
    // Schwellwertbildung Saturation für das linke Auge
    threshold(mouthPlanes[1], mouthPlanes[1], 100, 255, cv::THRESH_BINARY);
    // SchwellenwetBildung Value für das linke Auge
    threshold(mouthPlanes[2], mouthPlanes[2], 50, 255, cv::THRESH_BINARY);
    // Kombination aller Masken
    multiply(mouthPlanes[2], mouthPlanes[1], mouthPlanes[2]);
    //multiply(eyePlanes[0], eyePlanes[2], eyePlanes[0]);
    
    return mouthPlanes[2];

}