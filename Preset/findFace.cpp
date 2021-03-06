#include <opencv2/objdetect/objdetect.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>

#include <iostream>
#include <stdio.h>
#include <algorithm>

#include "findFace.h"



findFace::findFace()

{
    //Laden der CasscadeClassifier Daten
    eye_cascade.load("/Users/benutzer/Dropbox/WS2013:2014/AVPRG/Projekt/Recognition Test/eyes.xml");
    face_cascade.load("/Users/benutzer/Dropbox/WS2013:2014/AVPRG/Projekt/Recognition Test/face.xml");
    mouth_cascade.load("/Users/benutzer/Dropbox/WS2013:2014/AVPRG/Projekt/Recognition Test/mouth2.xml");
    
    //Webcam ansteuern
    captureDevice.open(0);
}

findFace::~findFace(void){}

cv::Mat findFace::drawOutput(cv::Mat mouthOverlay, cv::Mat eyeOverlay){
    
    //Webcamframe zwischenspeichern
    captureFrame.copyTo(outputFrame);
    
    //Mund- und Augenframe in BGR umwandeln
    cv::cvtColor(eyeOverlay, eyeOverlay, CV_GRAY2BGR);
    cv::cvtColor(mouthOverlay, mouthOverlay, CV_GRAY2BGR);
    
    //Rechtecke an Mund. und Augenpostition erzeugen
    cv::Rect eyeRoi( eyePos, cv::Size( eyeWidth, eyeHeight ));
    cv::Rect mouthRoi( mouthPos, cv::Size( mouthWidth, mouthHeight ));
    
    //Bereich auf Ausgabeframe den Rechtecken zuweisen
    cv::Mat mouthDestinationROI = outputFrame( mouthRoi );
    cv::Mat eyeDestinationROI = outputFrame( eyeRoi );
    
    //Farben invertieren
    cv::subtract(cv::Scalar(255),mouthOverlay, mouthOverlay);
    
    //Rechtecke mit Mund und Augen füllen
    eyeOverlay.copyTo( eyeDestinationROI );
    mouthOverlay.copyTo( mouthDestinationROI );
    
    
    return outputFrame;

}

void findFace::detectFace(){

    //neuen Frame laden
    captureDevice>>captureFrame;
    
    //Bild der Webcam Horizontal spiegeln
    flip(captureFrame, captureFrame, 1);
    
    //geladenen Frame in Graustufenbild umwandeln und nachjustieren
    cvtColor(captureFrame, grayscaleFrame, CV_BGR2GRAY);
    equalizeHist(grayscaleFrame, grayscaleFrame);
    //equalizeHist(grayscaleFrame, grayscaleFrame);

    //Gesichter finden und in Array schreiben
    face_cascade.detectMultiScale(grayscaleFrame, faces, 1.1, 3, CV_HAAR_FIND_BIGGEST_OBJECT|CV_HAAR_SCALE_IMAGE, cv::Size(30,30));
    
    //Wenn ein gesicht gefunden wurde dann...
    if(faces.size() > 0){
        
        //Mittelpunkt des Gesichts berechnen
        faceHeight = faces[0].height;
        faceWidth = faces[0].width;
        
        facePos.x = faces[0].x +  faceWidth*0.5;
        facePos.y = faces[0].y +  faceHeight*0.5;
        
        grayscaleFrame = grayscaleFrame(faces[0]);

        faceFrame = captureFrame(faces[0]);

        //Mund suchen und im Array speichern
        mouth_cascade.detectMultiScale(grayscaleFrame(cv::Rect(0,faceHeight/2,faceWidth, faceHeight/2)), mouth, 1.1, 3, CV_HAAR_FIND_BIGGEST_OBJECT|CV_HAAR_SCALE_IMAGE, cv::Size(30,30));
        
        //Wenn Mund gefunden dann...
        if(mouth.size() > 0){
            
            mouthHeight = mouth[0].height;
            mouthWidth = mouth[0].width;

            mouthPos.x = faces[0].x + mouth[0].x;
            mouthPos.y = faces[0].y + mouth[0].y + faceHeight/2;
            mouth[0].y += faceHeight/2;
            
            mouthFrame = faceFrame(mouth[0]);

        }

        //Augen finden und im Array speichern
        eye_cascade.detectMultiScale(grayscaleFrame(cv::Rect(0,0,faceWidth/2, faceHeight)), eyes, 1.1, 6, CV_HAAR_FIND_BIGGEST_OBJECT|CV_HAAR_SCALE_IMAGE, cv::Size(30,30));
        
        if(eyes.size() > 0){
            
            eyeHeight = eyes[0].height;
            eyeWidth = eyes[0].width;

            eyePos.x = faces[0].x + eyes[0].x;
            eyePos.y = faces[0].y + eyes[0].y;

            eyeFrame = faceFrame(eyes[0]);

        }
    }
}

cv::Mat findFace::getEyeROI(){
    return eyeFrame;
}

cv::Mat findFace::getMouthROI(){
    return mouthFrame;
}

cv::Point findFace::getEyePos(){
    return eyePos;
}

cv::Point findFace::getMouthPos(){
    return mouthPos;
}


int findFace::getEyeWidth(){
    return eyeWidth;
}
int findFace::getEyeHeight(){
    return eyeHeight;
}
int findFace::getMouthWidth(){
    return mouthWidth;
}
int findFace::getMouthHeight(){
    return mouthHeight;
}

cv::Mat findFace::getCaptureFrame(){
    return captureFrame;
}

bool findFace::hasFace(){

    if(faces.size() > 0 ){
        return true;
    }
    else{ return false;}
    
}

