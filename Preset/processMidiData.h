
#include  <opencv2/opencv.hpp>
#ifndef Preset_processMidiData_h
#define Preset_processMidiData_h


class processMidiData {
    
public:
    processMidiData();
    ~processMidiData(void);
 
    
    
    cv::Mat eyeTracking(cv::Mat eyeFrame);
    cv::Mat mouthTracking(cv::Mat mouthFrame);
    int processEyeData(cv::Mat eyePlane);
    int processMouthData(cv:: Mat mouthPlane);
    
    
private:
    
    int eyeHigh;
    int eyeLow;
    
    int mouthHL;
    int mouthHR;
    int mouthLL;
    int mouthLR;
    
    
    cv::Mat eyeFrameHSV;
    cv::Mat mouthFrameHSV;
    cv::Mat eyeTracked;
    cv::Mat mouthTracked;
    std::vector<cv::Mat> eyePlanes;
    std::vector<cv::Mat> mouthPlanes;

    
    
};


#endif
