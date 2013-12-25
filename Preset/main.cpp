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
	//Casscade Classiefier für Gesicht, Augen und Mund Deklarieren
	CascadeClassifier face_cascade;
    CascadeClassifier eye_cascade;
    CascadeClassifier mouth_cascade;
    
	//XML Bibliotheken zuweisen
	eye_cascade.load("/Users/benutzer/Dropbox/WS2013:2014/AVPRG/Projekt/Recognition Test/eyes.xml");
    face_cascade.load("/Users/benutzer/Dropbox/WS2013:2014/AVPRG/Projekt/Recognition Test/face.xml");
    mouth_cascade.load("/Users/benutzer/Dropbox/WS2013:2014/AVPRG/Projekt/Recognition Test/mouth2.xml");
    
	//VideoCaputer einrichten und auf WebCam einstellen
	VideoCapture captureDevice;
	captureDevice.open(0);
    
	//Benoetigte Mat Objekte für spaetere Berechnungen erstellen
	Mat captureFrame;
	Mat grayscaleFrame;
    Mat faceFrame;
    Mat mouthFrame;
    Mat eyeFrame;
    Mat faceGray;
    Mat eyeFrameHSV;
    
    float eyeCount[3];
 
    vector<Mat> eyePlanes;

    
	//Fenster erstellen
	namedWindow("outputCapture", 1);
    namedWindow("face", 1);
    namedWindow("mouth", 1);
    namedWindow("Eye", 1);
    
	//Enlosschliefe zur Gesichtserkennung
	while(true)
	{
		//neuen Frame laden
		captureDevice>>captureFrame;
        
        //Bild der Webcam Horizontal spiegeln
        flip(captureFrame, captureFrame, 1);
        
        
		//geladenen Frame in Graustufenbild umwandeln und nachjustieren
		cvtColor(captureFrame, grayscaleFrame, CV_BGR2GRAY);
		equalizeHist(grayscaleFrame, grayscaleFrame);
        
		//Vector Array fuer gefundene Gesichter erstellen
		std::vector<Rect> faces;
        
		//Gesichter finden und in Array schreiben
        face_cascade.detectMultiScale(grayscaleFrame, faces, 1.1, 3, CV_HAAR_FIND_BIGGEST_OBJECT|CV_HAAR_SCALE_IMAGE, Size(30,30));
        
        //Wenn ein gesicht gefunden wurde dann...
        if(faces.size() > 0){
            
            //Mittelpunkt des Gesichts berechnen
            Point center( faces[0].x + faces[0].width*0.5, faces[0].y + faces[0].height*0.5 );
            
            Mat faceGrayROI = grayscaleFrame(faces[0]);
            faceGrayROI.copyTo(faceGray);
            Mat faceROI = captureFrame(faces[0]);
            faceROI.copyTo(faceFrame);
            
            ellipse( captureFrame, center, Size( faces[0].width*0.4, faces[0].height*0.5), 0, 0, 360, Scalar( 255, 0, 0 ), 4, 8, 0 );
    
        
            //Vector Array fuer im Gesicht gefunden Mund erstellen
            std::vector<Rect> mouth;
            
            //Mat Objekt fuer Mund aus dem Gesamtbild ausschneiden
            Mat mouthROI = faceGray(Rect(0, faceGray.rows/2, faceGray.cols, faceGray.rows/2));
            
            //Mund suchen und im Array speichern
            mouth_cascade.detectMultiScale(mouthROI, mouth, 1.1, 3, CV_HAAR_FIND_BIGGEST_OBJECT|CV_HAAR_SCALE_IMAGE, Size(30,30));
            
            //Wenn Mund gefunden dann...
            if(mouth.size() > 0){
                
                //MittelPunkt der Mundes errechnen
                Point center(faces[0].x + mouth[0].x + mouth[0].width*0.5, faces[0].y + faceGray.rows/2 + mouth[0].y +  mouth[0].height*0.5 );
                
                Mat mundROI = faceFrame(Rect(mouth[0].x, faceGray.rows/2 + mouth[0].y, mouth[0].width, mouth[0].height));
                mundROI.copyTo(mouthFrame);
                
                ellipse( captureFrame, center, Size( mouth[0].width*0.4, mouth[0].height*0.5), 0, 0, 360, Scalar( 0, 255, 0 ), 4, 8, 0 );
            }
            
            
            //Vector Array fuer im Gesicht gefundes Auge erstellen
            std::vector<Rect> eyes;
            
            
            //Augen finden und im Array speichern
            eye_cascade.detectMultiScale(faceGray, eyes, 1.1, 3, CV_HAAR_FIND_BIGGEST_OBJECT|CV_HAAR_SCALE_IMAGE, Size(30,30));
            
            if(eyes.size() > 0){
                Point center(faces[0].x + eyes[0].x + eyes[0].width*0.5, faces[0].y + eyes[0].y +  eyes[0].height*0.5 );
                
                Mat eyesROI = faceFrame(eyes[0]);
                eyesROI.copyTo(eyeFrame);
                
                ellipse( captureFrame, center, Size( eyes[0].width*0.4, eyes[0].height*0.5), 0, 0, 360, Scalar( 0, 0, 255 ), 4, 8, 0 );
            }
            
            
            cvtColor(eyeFrame , eyeFrameHSV, CV_BGR2HSV);
            split(eyeFrame, eyePlanes);
            
            //Ergnisse ausgeben
            imshow("mouth", mouthFrame);
            imshow("face", faceFrame);
            imshow("Eye", eyePlanes[2]);
            
            for(int i = 0; i < eyeFrame.cols; i++){
                for(int j = 0; j < eyeFrame.rows; j++){
                    if(eyeFrameHSV.at<Vec3b>(i,j)[1] < 70) {
                        
                        eyeCount[2]++;
                        
                        if(i < eyeFrame.rows/2){
                            eyeCount[0]++;
                        }
                        else{
                            eyeCount[1]++;
                        }
                    }
                }
            }
            
            for(int i = 0; i < 2; i++){
            
                eyeCount[i] =  (int)((eyeCount[i]/eyeCount[2]) * 123.0) ;
            
            }
        
            
            cout << eyeCount[1] << endl;
            
            eyeCount[0]=0;
            eyeCount[1]=0;
            eyeCount[2]=0;

            
        }
        
        
        
        
        
        
        
        
		imshow("outputCapture", captureFrame);
        
        //pause for 33ms
		waitKey(33);
        
	}
    
    
	return 0;
    
}