#include  <opencv2/opencv.hpp>
#ifndef Preset_processMidiData_h
#define Preset_processMidiData_h

class processMidiData {
    
public:
    processMidiData();
    ~processMidiData(void);

    cv::Mat eyeTracking(int value, cv::Mat eyeFrame);
    cv::Mat mouthTracking(int value, cv::Mat mouthFrame);
    int processEyeData(int value, cv::Mat eyePlane);
    int processMouthData(int value, cv:: Mat mouthPlane);
    
private:
    
    int eyeLeft;
    int eyeMid;
    int eyeRight;
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
