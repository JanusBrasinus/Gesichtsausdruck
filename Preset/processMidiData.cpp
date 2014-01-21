#include <opencv2/objdetect/objdetect.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <iostream>
#include <stdio.h>
#include <algorithm>
#include "processMidiData.h"

processMidiData::processMidiData(){}

processMidiData::~processMidiData(void){}

int processMidiData::processEyeData(int value,cv::Mat eyeFrame){

    //Variablen bei Funktionsuafruf zurücksetzen
    eyeTracked = eyeTracking(value, eyeFrame);
    eyeLeft = 0;
    eyeMid = 0;
    eyeRight = 0;
    
    //Position der Pupille bestimmen und entsprechende Variablen setzen
    for(int i = eyeTracked.cols/3 ; i < eyeTracked.cols/3*2; i++){
        for(int j = eyeTracked.rows/3; j < eyeTracked.rows/3*2; j++){
            
            if(i > eyeTracked.cols/9*3 && i < eyeTracked.cols/9*4 && eyeTracked.at<uchar>(j,i) == 0)
            {
                eyeLeft++;
            }
            if(i > eyeTracked.cols/9*4 && i < eyeTracked.cols/9*5 && eyeTracked.at<uchar>(j,i) == 0)
            {
                eyeMid++;
            }
            if(i > eyeTracked.cols/9*5 && eyeTracked.at<uchar>(j,i) == 0)
            {
                eyeRight++;
            }
        }
    }
    
    //Rückgabewert für die Augen wählen
    if(eyeLeft > eyeRight && eyeLeft > eyeMid){
        return 1;
    }
    else if(eyeMid > eyeRight && eyeMid > eyeLeft){
        return 2;
    }
    else{
        return 3;
    }
}

int processMidiData::processMouthData( int value, cv::Mat mouthFrame){
    
    //Variablen bei Funktionsuafruf zurücksetzen
    mouthTracked = mouthTracking(value, mouthFrame);
    mouthHL = 0;
    mouthHR = 0;
    mouthLL = 0;
    mouthLR = 0;
    
    //Position der Lippen bestimmen und entsprechende Variablen setzen
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
    
    //Rückgabewert für den Mund wählen
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


cv::Mat processMidiData::eyeTracking(int value, cv::Mat eyeFrame){
    
    //Übergebenes Bild in HSV umwandeln und in Ebenen aufsplitten
    cvtColor(eyeFrame, eyeFrameHSV,CV_BGR2HSV);
    split(eyeFrameHSV, eyePlanes);
    
    // Schwellwertbildung Saturation für das linke Auge
    threshold(eyePlanes[1], eyePlanes[1], 10, 255, cv::THRESH_BINARY);
    
    // SchwellenwetBildung Value für das linke Auge
    threshold(eyePlanes[2], eyePlanes[2], value, 255, cv::THRESH_BINARY);
    
    // Kombination aller Masken
    multiply(eyePlanes[2], eyePlanes[1], eyePlanes[2]);
   
    //Versuch das Ergebnis zu optimieren, jedoch mit eher bescheidnem Erfolg
    
    //cv::erode(eyePlanes[2], eyePlanes[2],cv::Mat(cv::Size(3, 3), CV_8UC1));
    //cv::dilate(eyePlanes[2], eyePlanes[2],cv::Mat(cv::Size(5, 5), CV_8UC1));
    
    return eyePlanes[2];
}

cv::Mat processMidiData::mouthTracking(int value, cv::Mat mouthFrame){
    
    //Übergebenes Bild in HSV umwandeln und in Ebenen aufsplitten
    cvtColor(mouthFrame, mouthFrameHSV,CV_BGR2HSV);
    split(mouthFrameHSV, mouthPlanes);
    
    // Schwellwertbildung Hue für den Mund
    inRange(mouthPlanes[0], 10, 100, mouthPlanes[0]);
    
    // Schwellwertbildung Saturation für das linke Auge
    threshold(mouthPlanes[1], mouthPlanes[1], value, 255, cv::THRESH_BINARY);
    
    // SchwellenwetBildung Value für das linke Auge
    threshold(mouthPlanes[2], mouthPlanes[2], 50, 255, cv::THRESH_BINARY);

    // Kombination aller Masken
    multiply(mouthPlanes[2], mouthPlanes[1], mouthPlanes[2]);
    
    
    return mouthPlanes[2];
}