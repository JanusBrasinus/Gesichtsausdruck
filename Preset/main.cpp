#include <opencv2/objdetect/objdetect.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>

#include <iostream>
#include <stdio.h>

using namespace std;
using namespace cv;

int main(int argc, const char** argv)
{
	//create the cascade classifier object used for the face detection
	CascadeClassifier face_cascade;
    CascadeClassifier eye_cascade;
    CascadeClassifier mouth_cascade;
	//use the haarcascade_frontalface_alt.xml library
	eye_cascade.load("/Users/benutzer/Dropbox/WS2013:2014/AVPRG/Projekt/Recognition Test/eyes.xml");
    face_cascade.load("/Users/benutzer/Dropbox/WS2013:2014/AVPRG/Projekt/Recognition Test/face.xml");
    
    mouth_cascade.load("/Users/benutzer/Dropbox/WS2013:2014/AVPRG/Projekt/Recognition Test/mouth2.xml");
    
	//setup video capture device and link it to the first capture device
	VideoCapture captureDevice;
	captureDevice.open(0);
    
	//setup image files used in the capture process
	Mat captureFrame;
	Mat grayscaleFrame;
    Mat faceFrame;
    Mat mouthFrame;
    Mat eyeFrame;
    
    Mat faceGray;
    
	//create a window to present the results
	namedWindow("outputCapture", 1);
    namedWindow("face", 1);
    namedWindow("mouth", 1);
    namedWindow("Eye", 1);
    
	//create a loop to capture and find faces
	while(true)
	{
		//capture a new image frame
		captureDevice>>captureFrame;
        flip(captureFrame, captureFrame, 1);
        
        
		//convert captured image to gray scale and equalize
		cvtColor(captureFrame, grayscaleFrame, CV_BGR2GRAY);
		equalizeHist(grayscaleFrame, grayscaleFrame);
        
		//create a vector array to store the face found
		std::vector<Rect> faces;
        
		//find faces and store them in the vector array
        face_cascade.detectMultiScale(grayscaleFrame, faces, 1.1, 3, CV_HAAR_FIND_BIGGEST_OBJECT|CV_HAAR_SCALE_IMAGE, Size(30,30));
        
        if(faces.size() > 0){
            Point center( faces[0].x + faces[0].width*0.5, faces[0].y + faces[0].height*0.5 );
            
            Mat faceGrayROI = grayscaleFrame(faces[0]);
            faceGrayROI.copyTo(faceGray);
            Mat faceROI = captureFrame(faces[0]);
            faceROI.copyTo(faceFrame);
            
            ellipse( captureFrame, center, Size( faces[0].width*0.4, faces[0].height*0.5), 0, 0, 360, Scalar( 255, 0, 0 ), 4, 8, 0 );
    
        
            //create a vector array to store the face found
            std::vector<Rect> mouth;
            
            
            Mat mouthROI = faceGray(Rect(0, faceGray.rows/2, faceGray.cols, faceGray.rows/2));
            //find faces and store them in the vector array
            mouth_cascade.detectMultiScale(mouthROI, mouth, 1.1, 3, CV_HAAR_FIND_BIGGEST_OBJECT|CV_HAAR_SCALE_IMAGE, Size(30,30));
            
            
            if(mouth.size() > 0){
                Point center(faces[0].x + mouth[0].x + mouth[0].width*0.5, faces[0].y + faceGray.rows/2 + mouth[0].y +  mouth[0].height*0.5 );
                
                Mat mundROI = faceFrame(Rect(mouth[0].x, faceGray.rows/2 + mouth[0].y, mouth[0].width, mouth[0].height));
                mundROI.copyTo(mouthFrame);
                
                ellipse( captureFrame, center, Size( mouth[0].width*0.4, mouth[0].height*0.5), 0, 0, 360, Scalar( 0, 255, 0 ), 4, 8, 0 );
            }
            
            
            //create a vector array to store the face found
            std::vector<Rect> eyes;
            
            
            //find faces and store them in the vector array
            eye_cascade.detectMultiScale(faceGray, eyes, 1.1, 3, CV_HAAR_FIND_BIGGEST_OBJECT|CV_HAAR_SCALE_IMAGE, Size(30,30));
            
            if(eyes.size() > 0){
                Point center(faces[0].x + eyes[0].x + eyes[0].width*0.5, faces[0].y + eyes[0].y +  eyes[0].height*0.5 );
                
                Mat eyesROI = faceFrame(eyes[0]);
                eyesROI.copyTo(eyeFrame);
                
                ellipse( captureFrame, center, Size( eyes[0].width*0.4, eyes[0].height*0.5), 0, 0, 360, Scalar( 0, 0, 255 ), 4, 8, 0 );
            }
            
            //print the output
            imshow("mouth", mouthFrame);
            imshow("face", faceFrame);
            imshow("Eye", eyeFrame);
        }
		imshow("outputCapture", captureFrame);
        
        //pause for 33ms
		waitKey(33);
        
	}
    
    
	return 0;
    
}