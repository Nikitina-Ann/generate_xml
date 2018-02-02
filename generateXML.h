#ifndef GENERATEXML_H
#define GENERATEXML_H

#include "tinyxml2.h"
#include "inputVideo.h"
using namespace tinyxml2;
using namespace cv;

class generateXML {
public:
  XMLDocument doc;
  inputVideo video;
  string projectName;
  string outputName;

  Point outResolution;

  generateXML(string projectName, string videoName, string outputName, int outHeight, int outWidth);
  ~generateXML();

  XMLElement* getElementWithText(string name, string text);
  XMLElement* getElemClip();
  XMLElement* getElemSequence();
  XMLElement* getMedia(); //temp name, change later
  XMLElement* getVideoTrack(); //temp name, change later
  XMLElement* getLoggingInfo();
  XMLElement* getColorInfo();
  XMLElement* getLabels();
  XMLElement* getFormat();
  XMLElement* getRate();

  bool fillWithData() ;
};

#endif //GENERATEXML_H
