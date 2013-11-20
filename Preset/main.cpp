#include "opencv2/opencv.hpp"
#include <string>
#include <vector>
#include <iostream>
#include "centroid.h"
#include "cross.h"

using namespace cv;
using namespace std;


int main(){ 

    bool konfiguriert = false;
   
  	namedWindow("Original");
    namedWindow("Linkes Auge");
    namedWindow("Rechtes Auge");
    namedWindow("Mund");
	namedWindow("Konfiguration", CV_WINDOW_AUTOSIZE);
	resizeWindow("Konfiguration", 500, 450);

	createTrackbar("valueAugen", "Konfiguration", 0, 255);
	setTrackbarPos("valueAugen", "Konfiguration", 50);
    
	createTrackbar("minHueMund", "Konfiguration", 0, 180);
	setTrackbarPos("minHueMund", "Konfiguration", 160);

    createTrackbar("saturationMund", "Konfiguration", 0, 255);
	setTrackbarPos("saturationMund", "Konfiguration", 130);
	createTrackbar("valueMund", "Konfiguration", 0, 255);
	setTrackbarPos("valueMund", "Konfiguration", 50);
	
	Point centerMund;
	Point centerLinkesAuge;
	Point centerRechtesAuge;

	VideoCapture webCam;
    webCam.open(0);
    int width = webCam.get(CV_CAP_PROP_FRAME_WIDTH);
	int height = webCam.get(CV_CAP_PROP_FRAME_HEIGHT);
	
    cout << width;
    
	Mat videoFrameOriginal, camHSV, maskeGesicht, linkesAuge, rechtesAuge, mund;
    
    Mat mundRechteck(60, 120,CV_8UC1);
    Mat linkesAugenRechteck(40, 60,CV_8UC1);
    Mat rechtesAugenRechteck(40, 60,CV_8UC1);
    
	Mat ellipseZeichnen(webCam.get(CV_CAP_PROP_FRAME_HEIGHT), webCam.get(CV_CAP_PROP_FRAME_WIDTH), CV_8UC3, Scalar(0, 0, 0));

	
	ellipse(ellipseZeichnen,Point(webCam.get(CV_CAP_PROP_FRAME_WIDTH)/2, webCam.get(CV_CAP_PROP_FRAME_HEIGHT)/2),Size(150,213), 0.0, 0.0, 360.0, Scalar(255, 255, 255), -1);
	cvtColor(ellipseZeichnen, maskeGesicht, CV_BGR2GRAY);
    
    
    vector<Mat> planesLinkesAuge, planesRechtesAuge, planesMund, planes;

	while (true){
        

        Mat videoFrame;

      
		bool success = webCam.read(videoFrameOriginal);
		if (success == false){
			break;
		}
        
        flip(videoFrameOriginal, videoFrameOriginal, 1);
       	
        if(konfiguriert == false){
            videoFrameOriginal.copyTo(videoFrame, maskeGesicht);
        }
        if(konfiguriert == true){
            videoFrameOriginal.copyTo(videoFrame);
        }
        cvtColor(videoFrame,camHSV,CV_BGR2HSV);
        split(camHSV, planes);

		// Bildbereiche einteilen, ACHTUNG!! keine Kopie. Verweise sind auf Originalvideo
		linkesAuge = camHSV(Rect(0,0, width/2, height/2));
		rechtesAuge = camHSV(Rect(width/2, 0, width/2, height/2));
		mund = camHSV(Rect(0, height/2, width, height/2));

		split(linkesAuge, planesLinkesAuge);
		split(rechtesAuge, planesRechtesAuge);
		split(mund, planesMund);

        inRange(planesMund[0], (getTrackbarPos("minHueMund", "Konfiguration"))-20, (getTrackbarPos("minHueMund", "Konfiguration"))+20, planesMund[0]);

		threshold(planesMund[1], planesMund[1], getTrackbarPos("saturationMund", "Konfiguration"), 255, THRESH_BINARY);
        
        threshold(planesLinkesAuge[2], planesLinkesAuge[2], getTrackbarPos("valueAugen", "Konfiguration"), 255, THRESH_BINARY);
        
        threshold(planesRechtesAuge[2], planesRechtesAuge[2], getTrackbarPos("valueAugen", "Konfiguration"), 255, THRESH_BINARY);

		multiply(planesMund[0], planesMund[1], planesMund[0]);
		multiply(planesMund[0], planesMund[2], planesMund[0]);

        if (konfiguriert == false){
            centerMund = centroidOfWhitePixels(planesMund[0]);
            centerLinkesAuge = centroidOfWhitePixels(planesLinkesAuge[2]);
            centerRechtesAuge = centroidOfWhitePixels(planesRechtesAuge[2]);

        }

        rectangle(videoFrame, Rect(centerMund.x - 60, centerMund.y - 30 + height/2, 120, 60), Scalar(0,0,255), 1);
        rectangle(videoFrame, Rect(centerLinkesAuge.x - 30, centerLinkesAuge.y - 20, 60, 40), Scalar(0,0,255), 1);
        rectangle(videoFrame, Rect(centerRechtesAuge.x - 30 + width/2, centerRechtesAuge.y - 20, 60, 40), Scalar(0,0,255), 1);

        
        if (konfiguriert == true){
        linkesAugenRechteck = planesLinkesAuge[2](Rect(centerLinkesAuge.x - 30, centerLinkesAuge.y - 20, 60, 40));
        
        rechtesAugenRechteck = planesRechtesAuge[2](Rect((centerRechtesAuge.x)- 30, centerRechtesAuge.y - 20, 60, 40));
            
        mundRechteck = planesMund[0](Rect((centerMund.x)- 60, centerMund.y - 30, 120, 60));
         
        }
        if (konfiguriert == false){
        imshow("Mund", planesMund[0]);
		imshow("Linkes Auge", planesLinkesAuge[2]);
        imshow("Rechtes Auge", planesRechtesAuge[2]);
        }
        
        else{
        
            imshow("Linkes Auge", linkesAugenRechteck);
            imshow("Rechtes Auge", rechtesAugenRechteck);
            imshow("Mund", mundRechteck);
        }
        
        
        
        
        
        

        imshow( "Original", videoFrame );
        // 30 ms auf einen Tastendruck warten
		int key = waitKey(30);
		if (key != -1){
			konfiguriert = true;
            resizeWindow("Linkes Auge",60, 40);
            resizeWindow("Rechtes Auge",60, 40);
            resizeWindow("Rechtes Auge",120, 60);
            destroyWindow("Konfiguration");
		}
	}
    
    destroyAllWindows();
    
    

    
    /*
	

	while(true){
		Mat videoFrame;
		Mat mund;
		Mat augen;
		bool success = webCam.read(videoFrame);
		if (success == false){
			break;
		}

	}
	*/
    
    waitKey(0);
    return 0;
}