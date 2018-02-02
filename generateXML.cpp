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

  clip->InsertEndChild(getMedia());
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

XMLElement* generateXML::getMedia() { //temp name, change later
    XMLElement* media = doc.NewElement("media");
    XMLElement* video = doc.NewElement("video");
    video->InsertEndChild(getVideoTrack());
    media->InsertEndChild(video);

}

XMLElement* generateXML::getVideoTrack() { //temp name, change later
    XMLElement* track = doc.NewElement("track");
    XMLElement* clipitem = doc.NewElement("clipitem");

    clipitem->SetAttribute("id","clipitem-1");
    clipitem->InsertEndChild(getElementWithText("masterclipid","masterclipid-1"));
    clipitem->InsertEndChild(getElementWithText("name", video.videoName));
    clipitem->InsertEndChild(getRate());
    clipitem->InsertEndChild(getElementWithText("alphatype","none"));
    clipitem->InsertEndChild(getElementWithText("pixelaspectratio","square"));
    clipitem->InsertEndChild(getElementWithText("anamorphic","FALSE"));

    XMLElement* file = doc.NewElement("file");
    file->SetAttribute("id","file-1");
    file->InsertEndChild(getElementWithText("name", "placeholder")); //fix latter
    file->InsertEndChild(getElementWithText("pathurl", "placeholder")); //fix latter
    file->InsertEndChild(getRate());
    file->InsertEndChild(getElementWithText("duration", "325"));
    XMLElement* timecode = doc.NewElement("timecode");

    timecode->InsertEndChild(getRate());
    timecode->InsertEndChild(getElementWithText("string", "00:00:00:00"));
    timecode->InsertEndChild(getElementWithText("frame", "0"));
    timecode->InsertEndChild(getElementWithText("displayformat", "NDF"));
    file->InsertEndChild(timecode);


    XMLElement* media = doc.NewElement("media");

    XMLElement* video = doc.NewElement("video");
    XMLElement* samplecharacteristicsVideo = doc.NewElement("samplecharacteristics");
    samplecharacteristicsVideo->InsertEndChild(getRate());
    samplecharacteristicsVideo->InsertEndChild(getElementWithText("width", "1280"));
    samplecharacteristicsVideo->InsertEndChild(getElementWithText("height", "720"));
    samplecharacteristicsVideo->InsertEndChild(getElementWithText("anamorphic", "FALSE"));
    samplecharacteristicsVideo->InsertEndChild(getElementWithText("pixelaspectratio", "square"));
    samplecharacteristicsVideo->InsertEndChild(getElementWithText("fielddominance", "none"));
    video->InsertEndChild(samplecharacteristicsVideo);
    media->InsertEndChild(video);

    XMLElement* audio = doc.NewElement("audio");
    XMLElement* samplecharacteristicsAudio = doc.NewElement("samplecharacteristics");
    samplecharacteristicsAudio->InsertEndChild(getElementWithText("depth", "16"));
    samplecharacteristicsAudio->InsertEndChild(getElementWithText("samplerate", "48000"));
    audio->InsertEndChild(samplecharacteristicsAudio);
    audio->InsertEndChild(getElementWithText("channelcount", "2"));
    media->InsertEndChild(audio);
    file->InsertEndChild(media);

    clipitem->InsertEndChild(file);

    clipitem->InsertEndChild(getLink("clipitem-1", "video", 1, 1, -1));
    clipitem->InsertEndChild(getLink("clipitem-2", "audio", 2, 1, 1));
    clipitem->InsertEndChild(getLink("clipitem-3", "audio", 3, 1, 1));

    track->InsertEndChild(clipitem);
    return track;
}

XMLElement* generateXML::getLink(std::string linkref, std::string type, int track, int clip, int group) {
    XMLElement* link = doc.NewElement("link");
    link->InsertEndChild(getElementWithText("linkclipref", linkref));
    link->InsertEndChild(getElementWithText("mediatype", type));
    link->InsertEndChild(getElementWithText("trackindex", std::to_string(track)));
    link->InsertEndChild(getElementWithText("clipindex", std::to_string(clip)));
    if(group >= 0)
        link->InsertEndChild(getElementWithText("groupindex", std::to_string(group)));
    return link;
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
