
#include  <opencv2/opencv.hpp>
#ifndef Preset_findFace_h
#define Preset_findFace_h


class findFace {

public:
    findFace();
    ~findFace(void);
    
    
    void detectFace();
    cv::Mat drawEllipse();
    cv::Mat getCaptureFrame();
    cv::Mat getEyeROI();
    cv::Mat getMouthROI();
    cv::Point getEyePos();
    cv::Point getMouthPos();
    bool hasFace();
    int getEyeWidth();
    int getEyeHeight();
    int getMouthWidth();
    int getMouthHeight();
    
    
    
    
    
private:
    
    int eyeHeight;
    int eyeWidth;
    int mouthHeight;
    int mouthWidth;
    int faceHeight;
    int faceWidth;
    
    cv::Mat eyeROI;
    cv::Mat mouthROI;
    
    cv::Mat captureFrame;
    cv::Mat outputFrame;
	cv::Mat grayscaleFrame;
    cv::Mat faceFrame;
    cv::Mat mouthFrame;
    cv::Mat eyeFrame;
    //cv::Mat faceGray;
    //cv::Mat eyeFrameHSV;
    
    cv::Point eyePos;
    cv::Point mouthPos;
    cv::Point facePos;
    
    cv::CascadeClassifier face_cascade;
    cv::CascadeClassifier eye_cascade;
    cv::CascadeClassifier mouth_cascade;
    
    cv::VideoCapture captureDevice;
    
    //cv::Scalar eyeColor;
    //cv::Scalar mouthColor;
    
    
    std::vector<cv::Rect> faces;
    std::vector<cv::Rect> mouth;
    std::vector<cv::Rect> eyes;


};


#endif
