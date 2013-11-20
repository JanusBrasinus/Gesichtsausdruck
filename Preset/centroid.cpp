#include <opencv2/opencv.hpp>
#include "centroid.h"
using namespace cv;

Point centroidOfWhitePixels(const Mat& image){
	int sumx = 0;
	int sumy = 0;
	int count = 0;
	for(int x = 0; x < image.cols; x++){
		for (int y = 0; y < image.rows; y++){
			if (image.at<uchar>(y,x) == 255){
				sumx += x;
				sumy += y;
				count++;
			}
		}
	}
	if (count > 0){
		return Point(sumx/count, sumy/count);
	}
	else {
		return Point(-1,-1);
	}
}
