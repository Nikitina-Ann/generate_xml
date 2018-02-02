#include <iostream>
#include <string>
#include <unistd.h>
#include <getopt.h>

#include "generateXML.h"


using namespace std;

static const struct option options[] = {
    {   "project", required_argument, NULL, 'p' },
    {   "video", required_argument, NULL, 'v' },
    {   "xml", required_argument, NULL, 'x' },

    {   "out_height", required_argument,  NULL, 1},
    {   "out_width", required_argument, NULL, 2},

    {   "help", no_argument, NULL, 3},

    {   NULL, 0, NULL, 0 },
};

std::string help()
{
    static std::stringstream help;
    help << "Input arguments : " << std::endl
       << "-p --project    project name" << std::endl
       << "-v --video      video name" << std::endl
       << "-x --xml        output xml name" << std::endl
       << "--out_height" << std::endl
       << "--out_width" << std::endl;

    return help.str();
}


int main(int argc, char* argv[]) {
  string projectName;
  string videoName;
  string xmlName;
  int outHeight = 2160;
  int outWidth = 3840;

  int index = 0;
  int opt;
  while ((opt = getopt_long(argc, argv, "p:v:x:", options, &index)) >= 0) {
    switch (opt) {
          case 'p':
                projectName = string(optarg);
                break;
            case 'v':
                videoName = string(optarg);
                break;
            case 'x':
                xmlName = string(optarg);
                break;
            case 1:
                outHeight = atoi(optarg);
                break;
            case 2:
                outWidth = atoi(optarg);
                break;
            case 3:
              std::cout << help();
              return -1;
              break;
            default:
              cout << help();
              return -1;
        }
    }
    if(projectName.empty() || videoName.empty() || xmlName.empty()) {
      cout << help();
      return -1;
    }

  generateXML xml(projectName, videoName, xmlName, outHeight, outWidth);

  if (!xml.fillWithData()) {
      cerr << "Error create xml file" << endl;
  } else {
    cout << "Success! " << endl;
  }
  return 0;
}
