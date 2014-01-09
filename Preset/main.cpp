
#include "findFace.h"
#include "processMidiData.h"
#include "sendMidi.h"
//#include "GUI.h"
#include <opencv2/objdetect/objdetect.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>

#include <iostream>
#include <stdio.h>
#include <algorithm>


using namespace std;
using namespace cv;

int main(int argc, const char** argv)
{

    findFace face;
    processMidiData process;
    sendMidi send;
    
	//Fenster erstellen

    namedWindow("Mouth", 1);
    moveWindow("Mouth", 0,0);
    namedWindow("Eye", 1);
    moveWindow("Eye", 300,0);
    namedWindow("Config", 1);
    moveWindow("Config", 300, 200);
    
    createTrackbar("Augen", "Config", 0, 255);
	setTrackbarPos("Augen", "Config", 30);
    createTrackbar("Mund", "Config", 0, 180);
	setTrackbarPos("Mund", "Config", 100);
    
    
	while(true)
	{
        face.detectFace();
        

        if(face.hasFace()){
        
            imshow("Mouth", process.mouthTracking(getTrackbarPos("Mund", "Config"), face.getMouthROI()));
            imshow("Eye", process.eyeTracking(getTrackbarPos("Augen", "Config"), face.getEyeROI()));
            send.sendMessage(process.processEyeData(getTrackbarPos("Augen", "Config"), face.getEyeROI()), process.processMouthData(getTrackbarPos("Mund", "Config"), face.getMouthROI()));

        }
        

		waitKey(42);

	
    }
    return 0;
}