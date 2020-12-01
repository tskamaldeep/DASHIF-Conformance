//
// Created by Kamaldeep Tumkur on 28/11/20.
//

#include "ConformanceMPDDataModel.h"

using namespace conformance::parser;

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
        maxwidth_ = std::move (widthval);
    }
    else if (!max and min) {
        minwidth_ = std::move (widthval);
    }
    else if (!max and !min) {
        adwidth_ = std::move (widthval);
    }
    else {
        std::cerr << "Invalid width parameter provided with adaptation set ID: " << adID_ << std::endl;
        std::cerr << "Adaptation set width setting failed." << std::endl;
        return;
    }
}

void ConformanceMPDAdaptationSet::setHeightForAdaptationSet(std::size_t heightval, bool max, bool min) {
    if (max and !min) {
        maxheight_ = std::move (heightval);
    }
    else if (!max and min) {
        minheight_ = std::move (heightval);
    }
    else if (!max and !min) {
        adheight_ = std::move (heightval);
    }
    else {
        std::cerr << "Invalid height parameter provided with adaptation set ID: " << adID_ << std::endl;
        std::cerr << "Adaptation set height setting failed." << std::endl;
        return;
    }
}

void ConformanceMPDAdaptationSet::setFrameRateForAdaptationSet(std::size_t frate, bool max) {
    if (max) {
        maxframerate_ = std::move (frate);
    }
    else if (!max ) {
        framerate_ = std::move (frate);
    }
    else {
        std::cerr << "Invalid framerate provided with adaptation set ID: " << adID_ << std::endl;
        std::cerr << "Adaptation set framerate setting failed." << std::endl;
        return;
    }
}

std::size_t ConformanceMPDAdaptationSet::addRepresentationToAdaptationSet(ConformanceMPDRepresentation &rep) {
    std::list<ConformanceMPDRepresentation> reps = this->representations();
    std::list<ConformanceMPDRepresentation>::iterator repIter;

    for (repIter=reps.begin(); repIter!=reps.end(); ++repIter) {
        if (!repIter->repID().compare(rep.repID())) {
            // Representation is already added to the adaptation set.
            std::cerr << "Given representation " << std::string(rep.repID()) << " already added to the adaptation set "
                      << adID_ << std::endl;
            return numrepresentations_;
        }
    }

    representations_.push_back(rep);
    numrepresentations_+=1;

    // Return number of reps or the ID of the added rep.
    return numrepresentations_;
}