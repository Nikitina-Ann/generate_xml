#ifndef INPUTVIDEO_H
#define INPUTVIDEO_H

#include <string>
#include "opencv2/opencv.hpp"

using namespace cv;
using namespace std;

class inputVideo {
public:
  VideoCapture videoCapture;
  string videoName;
  int fps;
  int width;
  int height;

	inputVideo(string videoName);
	virtual ~inputVideo();



};
#endif //INPUTVIDEO_H
