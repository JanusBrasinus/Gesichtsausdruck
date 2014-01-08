
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
	namedWindow("outputCapture", 1);
    namedWindow("Face", 1);
    namedWindow("Mouth", 1);
    namedWindow("Eye", 1);

	while(true)
	{
        face.detectFace();
        

        if(face.hasFace()){
        
            imshow("Mouth", process.mouthTracking(face.getMouthROI()));
            imshow("Eye", process.eyeTracking(face.getEyeROI()));
            send.sendMessage(process.processEyeData(face.getEyeROI()), process.processMouthData(face.getMouthROI()));

        }
        
        
        cout << "lol";
		waitKey(33);

	
    }
    return 0;
}