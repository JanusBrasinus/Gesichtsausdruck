#include "findFace.h"
#include "processMidiData.h"
#include "sendMidi.h"
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

    namedWindow("Face", 1);
    moveWindow("Face", 300,222);

    namedWindow("Config", 1);
    moveWindow("Config", 520, 200);
    resizeWindow("Config", 200, 20);
    
    createTrackbar("Augen", "Config", 0, 255);
	setTrackbarPos("Augen", "Config", 30);
    createTrackbar("Mund", "Config", 0, 180);
	setTrackbarPos("Mund", "Config", 100);
    
	while(true)
	{
        // Gesicht erkennen
        face.detectFace();
        
        if(face.hasFace()){
            
            //Ausgabe berechnen und anzeigen
            imshow("Face", face.drawOutput(process.mouthTracking(getTrackbarPos("Mund", "Config"),face.getMouthROI()),
                                           process.eyeTracking(getTrackbarPos("Augen", "Config"),face.getEyeROI())));

            // errechnete Midi Daten senden
            send.sendMessage(process.processEyeData(getTrackbarPos("Augen", "Config"), face.getEyeROI()), process.processMouthData(getTrackbarPos("Mund", "Config"), face.getMouthROI()));

        }
		waitKey(42);
    }
    return 0;
}