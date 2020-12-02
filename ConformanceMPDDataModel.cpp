//
// Created by Kamaldeep Tumkur on 28/11/20.
//

#include "ConformanceMPDDataModel.h"

using namespace conformance::parser;

ConformanceMPDSegmentTemplate::ConformanceMPDSegmentTemplate(std::size_t startnum, std::string initialization,
                                                             std::size_t dur, std::string mediaStr,
                                                             std::size_t timescale,
                                                             std::size_t pts) :
        startNum_(startnum), initializationStr_(initialization),
        duration_(dur), mediastr_(mediaStr), timescale_(timescale), pts_(pts) {

    // Check the extension of mediastr and initialization of the segment template.
    // Supported extensions table available for the version in force?

    std::string ext_substr = initialization.substr(initialization.size() - 4);
    std::string ext_substr2 = mediaStr.substr(mediaStr.size() - 4);

    if (!ext_substr.compare(".mp4") or !ext_substr2.compare(".mp4")) {
        std::cerr << "Unknown initialization string present in the segment template object.\n" << "Found: "
                  << ext_substr << std::endl;
    }
}

void ConformanceMPDAdaptationSet::setPARForAdaptationSet(const std::string adpar) {
    // TODO: Refine check. Only "16:9" or "4:3" allowed for now.
    if (!adpar.compare(PAR_16_9) || !adpar.compare(PAR_4_3)) {
        std::cerr << "Invalid pixel aspect ratio provided with adaptation set ID: " << adID_ << std::endl;
        std::cerr << "Adaptation set PAR test failed." << std::endl;
        return;
    }

    par_ = std::move(adpar);
}

void ConformanceMPDAdaptationSet::setContentTypeForAdaptationSet(std::size_t ctype) {
    // TODO: Refine check. Only "16:9" or "4:3" allowed for now.
    switch (ctype) {
        case AdaptationSetContentType::CONTENT_TYPE_VIDEO:
        case AdaptationSetContentType::CONTENT_TYPE_IMAGE:
        case AdaptationSetContentType::CONTENT_TYPE_AUDIO:
        case AdaptationSetContentType::CONTENT_TYPE_TEXT:
            contentType_ = std::move(ctype);
            break;

        default: {
            std::cerr << "Invalid content-type provided with adaptation set ID: " << adID_ << std::endl;
            std::cerr << "Adaptation set contentType setting failed." << std::endl;
            break;
        }
    }
}

void ConformanceMPDAdaptationSet::setBitstreamSwitchingForAdaptationSet(bool bsswitching) {
    bitstreamswitching_ = std::move(bsswitching);
}

void ConformanceMPDAdaptationSet::setWidthForAdaptationSet(std::size_t widthval, bool max, bool min) {
    if (max and !min) {
        maxwidth_ = std::move(widthval);
    } else if (!max and min) {
        minwidth_ = std::move(widthval);
    } else if (!max and !min) {
        adwidth_ = std::move(widthval);
    } else {
        std::cerr << "Invalid width parameter provided with adaptation set ID: " << adID_ << std::endl;
        std::cerr << "Adaptation set width setting failed." << std::endl;
        return;
    }
}

void ConformanceMPDAdaptationSet::setHeightForAdaptationSet(std::size_t heightval, bool max, bool min) {
    if (max and !min) {
        maxheight_ = std::move(heightval);
    } else if (!max and min) {
        minheight_ = std::move(heightval);
    } else if (!max and !min) {
        adheight_ = std::move(heightval);
    } else {
        std::cerr << "Invalid height parameter provided with adaptation set ID: " << adID_ << std::endl;
        std::cerr << "Adaptation set height setting failed." << std::endl;
        return;
    }
}

void ConformanceMPDAdaptationSet::setFrameRateForAdaptationSet(std::size_t frate, bool max) {
    if (max) {
        maxframerate_ = std::move(frate);
    } else if (!max) {
        framerate_ = std::move(frate);
    } else {
        std::cerr << "Invalid framerate provided with adaptation set ID: " << adID_ << std::endl;
        std::cerr << "Adaptation set framerate setting failed." << std::endl;
        return;
    }
}

std::size_t ConformanceMPDRepresentation::addSegmentTemplateToRepresentation(ConformanceMPDSegmentTemplate segtmp) {
    std::list<ConformanceMPDSegmentTemplate> segs = this->segmentTemplates();
    std::list<ConformanceMPDSegmentTemplate>::iterator segIter;
    std::int16_t segcount = 0;

    for (segIter = segs.begin(); segIter != segs.end(); ++segIter) {
        segcount++;
    }

    if (segcount > numsegmenttemplates_) {
        std::cerr << "Count mismatch in aggregating segment templates" << std::endl;
        std::cerr << "Stopping the task of adding a segment template to the representation." << std::endl;
        return segcount;
    }

    // Add the collection to the back of the list.
    segmentTemplates_.push_back(segtmp);
    numsegmenttemplates_ += 1;
    return numsegmenttemplates_;
}

std::size_t ConformanceMPDAdaptationSet::addRepresentationToAdaptationSet(ConformanceMPDRepresentation &rep) {
    std::list<ConformanceMPDRepresentation> reps = this->representations();
    std::list<ConformanceMPDRepresentation>::iterator repIter;

    for (repIter = reps.begin(); repIter != reps.end(); ++repIter) {
        if (!repIter->repID().compare(rep.repID())) {
            // Representation is already added to the adaptation set.
            std::cerr << "Given representation " << std::string(rep.repID()) << " already added to the adaptation set "
                      << adID_ << std::endl;
            return numrepresentations_;
        }
    }

    representations_.push_back(rep);
    numrepresentations_ += 1;

    // Return number of reps or the ID of the added rep.
    return numrepresentations_;
}