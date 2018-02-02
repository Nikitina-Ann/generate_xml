#include "inputVideo.h"

inputVideo::inputVideo(string videoName) : videoName(videoName), videoCapture(videoName)
{
  fps = videoCapture.get(CV_CAP_PROP_FPS);
  width = videoCapture.get(CV_CAP_PROP_FRAME_WIDTH);
  height = videoCapture.get(CV_CAP_PROP_FRAME_HEIGHT);
}

inputVideo::~inputVideo() {

}
