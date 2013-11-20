#include "cross.h"
using namespace cv;


void cross(Mat& image, Point center, int length, Scalar color){
	if(center.x > 0 && center.y > 0){
		line(image, center-Point(0, length), center+Point(0,length), color, 1);
		line(image, center-Point(length, 0), center+Point(length, 0), color, 1);
	}
}
