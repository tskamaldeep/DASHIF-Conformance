//
// Created by Kamaldeep Tumkur on 31/08/20.
//

#include "ConformanceMPDParser.h"
#include "ConformanceException.h"

using namespace conformance::parser;
using namespace conformance::exception;

bool ConformanceMPDParser::parseXML() {
    bool result = false;

    if (xmldata_.size() <= 0) {
        // Prepare a conformance exception for an XML with invalid length.
        // Count an invalid MPD XML as a media exception.
        ConformanceException *mediaExc = new ConformanceException(conformance::exception::mediaexceptionhash);
        std::string descShort = mediaexceptionstrshort + ": " + std::string(__func__);
        std::string descLong = descShort + "\n" + "XML size in memory is invalid. XML Parse failure.";

        // Set the exception details.
        mediaExc->exceptionStrShort(mediaexceptionhash, descShort);
        mediaExc->exceptionStrLong(mediaexceptionhash, descLong);

        if (this->parserThrowMessages()) {
            // The serialized details object would be better.
            throw (mediaExc);
        }
        return result;
    }

    // Start the parseXML routine.
    xmlpp::Document *doc = parser_->get_document();
    xmlpp::Element *enode = doc->get_root_node();

    xmlpp::Element::NodeList nlist = enode->get_children();
    xmlpp::Element::NodeList::iterator *nodelistiter = new xmlpp::Element::NodeList::iterator ();

    for (*nodelistiter = nlist.begin(); *nodelistiter != nlist.end(); nodelistiter++) {
        // Parse the node elements with the well known MPD params storage.
        // Store in memory and store into some kind of available disk cache. memcache?
        // Use the system file or a tmp location on disk?
    }

    result = true;
    return result;
}