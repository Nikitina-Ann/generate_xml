#include "generateXML.h"

generateXML::generateXML(string projectName, string videoName, string outputName, int outHeight, int outWidth) :
                        video(videoName), projectName(projectName), outputName(outputName), outResolution(outWidth, outHeight) {
}

bool generateXML::fillWithData() {
    XMLDeclaration * decl = doc.NewDeclaration("xml version=\"1.0\" encoding=\"UTF-8\"");
    doc.InsertEndChild(decl);

    XMLElement * xmeml = doc.NewElement("xmeml");
    xmeml->SetAttribute("version","4");

    XMLElement * project = doc.NewElement("project");

    XMLElement * name = doc.NewElement("name");
    name->SetText(projectName.c_str());
    project->InsertEndChild(name);

    XMLElement * children = doc.NewElement("children");
    children->InsertEndChild(getElemClip());
    children->InsertEndChild(getElemSequence());

    project->InsertEndChild(children);
    xmeml->InsertEndChild(project);

    doc.InsertEndChild(xmeml);

    XMLError eResult = doc.SaveFile(outputName.c_str());

    if (eResult != XML_SUCCESS) {
      return false;
  }
  return true;
}

generateXML::~generateXML() {

}


XMLElement* generateXML::getElementWithText(string name, string text) {
  XMLElement * elem = doc.NewElement(name.c_str());
  elem-> SetText(text.c_str());
  return elem;
}

XMLElement* generateXML::getElemClip() {
  XMLElement* clip = doc.NewElement("clip");

  clip->InsertEndChild(getElementWithText("uuid", "1111244"));
  clip->InsertEndChild(getElementWithText("masterclipid","masterclipid-1"));
  clip->InsertEndChild(getElementWithText("ismasterclip", "TRUE"));
  clip->InsertEndChild(getElementWithText("duration", "325"));
  clip->InsertEndChild(getElementWithText("name", video.videoName));

  clip->InsertEndChild(getLoggingInfo());
  clip->InsertEndChild(getColorInfo());
  clip->InsertEndChild(getLabels());

  return clip;
}

XMLElement* generateXML::getElemSequence() {
  XMLElement* sequence = doc.NewElement("sequence");
  XMLElement* media = doc.NewElement("media");
  sequence->InsertEndChild(media);

  XMLElement* video = doc.NewElement("video");
  video->InsertEndChild(getFormat());
  media->InsertEndChild(video);

  return sequence;
}

XMLElement* generateXML::getLoggingInfo() {
  XMLElement* loggingInfo = doc.NewElement("loggingInfo");
  loggingInfo->InsertEndChild(doc.NewElement("description"));
  loggingInfo->InsertEndChild(doc.NewElement("scene"));
  loggingInfo->InsertEndChild(doc.NewElement("shottake"));
  loggingInfo->InsertEndChild(doc.NewElement("lognote"));
  loggingInfo->InsertEndChild(doc.NewElement("good"));
  loggingInfo->InsertEndChild(doc.NewElement("originalvideofilename"));
  loggingInfo->InsertEndChild(doc.NewElement("originalaudiofilename"));
  return loggingInfo;
}

XMLElement* generateXML::getColorInfo() {
  XMLElement* colorInfo = doc.NewElement("colorinfo");
  colorInfo->InsertEndChild(doc.NewElement("lut"));
  colorInfo->InsertEndChild(doc.NewElement("lut1"));
  colorInfo->InsertEndChild(doc.NewElement("asc_sop"));
  colorInfo->InsertEndChild(doc.NewElement("asc_sat"));
  colorInfo->InsertEndChild(doc.NewElement("lut2"));
  return colorInfo;
}

XMLElement* generateXML::getLabels() {
  XMLElement* labels = doc.NewElement("labels");
  labels->InsertEndChild(getElementWithText("labe2", "Iris"));
  return labels;
}

XMLElement* generateXML::getFormat() {
  XMLElement* format = doc.NewElement("format");
  XMLElement* samplecharacteristics = doc.NewElement("samplecharacteristics");
  format->InsertEndChild(samplecharacteristics);
  samplecharacteristics->InsertEndChild(getRate());

  XMLElement* codec = doc.NewElement("codec");
  codec->InsertEndChild(getElementWithText("name", "Apple ProRes 422"));

  XMLElement* appspecificdata = doc.NewElement("appspecificdata");
  appspecificdata->InsertEndChild(getElementWithText("appname", "Final Cut Pro"));
  appspecificdata->InsertEndChild(getElementWithText("appmanufacturer", "Apple Inc."));
  appspecificdata->InsertEndChild(getElementWithText("appversion", "7.0"));
  XMLElement* data = doc.NewElement("data");

  XMLElement* qtcodec = doc.NewElement("qtcodec");
  qtcodec->InsertEndChild(getElementWithText("codecname", "Apple ProRes 422"));
  qtcodec->InsertEndChild(getElementWithText("codectypename", "Apple ProRes 422"));
  qtcodec->InsertEndChild(getElementWithText("codectypecode", "apcn"));
  qtcodec->InsertEndChild(getElementWithText("codecvendorcode", "appl"));
  qtcodec->InsertEndChild(getElementWithText("spatialquality", "1024"));
  qtcodec->InsertEndChild(getElementWithText("temporalquality", "0"));
  qtcodec->InsertEndChild(getElementWithText("keyframerate", "0"));
  qtcodec->InsertEndChild(getElementWithText("datarate", "0"));
  data->InsertEndChild(qtcodec);

  appspecificdata->InsertEndChild(data);
  codec->InsertEndChild(appspecificdata);

  samplecharacteristics->InsertEndChild(codec);
  samplecharacteristics->InsertEndChild(getElementWithText("width", to_string(outResolution.x)));
  samplecharacteristics->InsertEndChild(getElementWithText("height", to_string(outResolution.y)));
  samplecharacteristics->InsertEndChild(getElementWithText("anamorphic", "FALSE"));
  samplecharacteristics->InsertEndChild(getElementWithText("pixelaspectratio", "square"));
  samplecharacteristics->InsertEndChild(getElementWithText("fielddominance", "none"));
  samplecharacteristics->InsertEndChild(getElementWithText("colordepth", "24"));
  return format;
}

XMLElement* generateXML::getRate() {
  XMLElement* rate = doc.NewElement("rate");
  rate->InsertEndChild(getElementWithText("timebase", to_string(video.fps)));
  rate->InsertEndChild(getElementWithText("ntsc", "FALSE"));
  return rate;
}
