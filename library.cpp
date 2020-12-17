#include "library.h"

#include <iostream>
#include <fstream>
#include "ConformanceMPDCheckSequence.h"
#include "ConformanceMPDDataModel.h"
#include "ConformanceMPDParser.h"

using namespace conformance::download;
using namespace conformance::parser;

int main(int argc, char **argv) {
    const std::string mpdurl = "https://dash.akamaized.net/akamai/bbb_30fps/bbb_30fps.mpd";

//    ConformanceMPDCheckSequence *mpdcs = new ConformanceMPDCheckSequence(mpdurl);
//    std::cout << mpdcs->currentSystemTime().time_since_epoch().count() << std::endl;

    ConformanceMPDDataModel *dm = new ConformanceMPDDataModel();

    const std::string fpath = "samples/MultiResMPEG2.mpd";
    std::ifstream xmlMPD(fpath, std::ios::binary);
    char *xmldata;
    int filelen;

    if (!xmlMPD.is_open()) {
        std::cout << "File open failure: " << fpath << endl;
    }
    else {
        // Seek till the end, get the length to initialize, then seek back?
        xmlMPD.seekg(0, xmlMPD.end);
        filelen = xmlMPD.tellg();
        xmlMPD.seekg(0, xmlMPD.beg);
        // Now initialize xmlData
        xmldata = new char [filelen];

        xmlMPD.read(reinterpret_cast<char *>(xmldata), filelen);

        // Try to instantiate an XML parser.
        // xmlparser should now initialize the entire MPD string.
        ConformanceMPDParser *xmlparser = new ConformanceMPDParser(xmldata, true, false, true);
        cout << xmlparser->xmlData() << endl;

        //bool parseresult = xmlparser->parseXML();

    }

    xmlMPD.close();
    delete [] xmldata;

    return 0;
}