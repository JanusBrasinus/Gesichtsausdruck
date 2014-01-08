
#include "findFace.h"
#include "processMidiData.h"
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
    //GUI gui;
    
    float eyeCount[3];
 
    vector<Mat> eyePlanes;

    
	//Fenster erstellen
	namedWindow("outputCapture", 1);
    namedWindow("Face", 1);
    namedWindow("Mouth", 1);
    namedWindow("Eye", 1);
    
	//Endlosschliefe zur Gesichtserkennung
	while(true)
	{
            face.detectFace();
            process.processEyeData(face.getEyeROI());
        
        
        
        
        
        
      
        
        
        if(face.hasFace()){
        
            imshow("Mouth", process.mouthTracking(face.getMouthROI()));
            //imshow("Eye", process.eyeTracking(face.getEyeROI()));
         
        }
        

        
            
            cout << process.processMouthData(face.getMouthROI()) << endl;
         
            eyeCount[0]=0;
            eyeCount[1]=0;
            eyeCount[2]=0;

            
        }
        

		//imshow("outputCapture", captureFrame);
        
        //pause for 33ms
		waitKey(33);
        
	

	return 0;
    
}