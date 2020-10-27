//
// Created by Kamaldeep Tumkur on 31/08/20.
//

#include <iostream>
#include <utility>
#include <memory>
#include "ConformanceMPDCheckSequence.h"
#include "ConformanceErrorLevels.h"

using namespace conformance::download;
using namespace conformance::exception;
using namespace std;

bool ConformanceMPDCheckSequence::checkURLValidity() {
    // Check the extension.
    // Check the prefix

    bool result = false;

    switch (this->MPDURLSchemeType()) {
        case conformance::download::MPDURLSCHEMETYPE::HTTP_PREFIX:
            // No HTTPS validations required if any.
            break;
        case conformance::download::MPDURLSCHEMETYPE::HTTPS_PREFIX:
            break;
        case conformance::download::MPDURLSCHEMETYPE::INVALID_PREFIX:
            // Throw a conformance exception.
            ConformanceException *mediaExc = new ConformanceException(conformance::exception::mediaexceptionhash);
            const char *excStringBase = std::string("Conformance Error: '%s'-'%s'\n").c_str();
            std::string descShort = mediaexceptionstrshort + ": " + std::string(__func__);

            // Set the exception details.
            mediaExc->exceptionStrShort(mediaexceptionhash, descShort);
            mediaExc->exceptionStrLong(mediaexceptionhash, descShort);
            // TODO: Complete the exception definition.
            break;
    }

// DEFINE WITH [[maybe_unused]]
//    const std::string MPDEXT = ".mpd";
//    const std::string HTTPPREFIX = "http://";
//    const std::string HTTPSPREFIX = "https://";
    const std::string PATHSEP = "/";


    // Find the path components.
    std::string murl = this->MPDURL();
    std::size_t firstsepindex = murl.find_first_of(PATHSEP);
    std::size_t lastsepindex = murl.find_last_of(PATHSEP);
    std::string urlbasename = murl.substr(lastsepindex + 1);
    std::string urldirname = murl.substr(firstsepindex + 1, lastsepindex);

    // TODO: Validate the status.
    // Finally return the status.
    return result;
}

bool checkMPDAvailability() {
    // Check presence of the MPD
    // Check download validity.

    return true;
}

bool redirectResponseCheck() {
    // Is the manifest downloadable
    // Does the manifest give a redirect response.

    return true;
}

bool ConformanceMPDCheckSequence::manifestTypeCheck() {
    // Is the manifest static type?
    // Is the manifest dynamic type?
    // Are the sub-manifests of the expected type?
    // Do the tags tally with the provided type.
    // Constraints which matter for the check
    // StaticMPDTypeConstraint
    // DynamicMPDTypeConstraint
    //

    std::array<int16_t, 2>::iterator *mpdtypecheckIter = new std::array<int16_t, 2>::iterator();
    for (*mpdtypecheckIter=MPDResponseConstraints_->begin(); *mpdtypecheckIter!=MPDResponseConstraints_->end(); *mpdtypecheckIter++) {
        constraints::ConformanceConstraint *typeConstraint = reinterpret_cast<constraints::ConformanceConstraint*>(*mpdtypecheckIter);
        // Get the set of definitions associated with the provided constraint of MPD type checks.

    }
    // return true;
}

bool refreshIntervalCheck() {
    // Is the manifest dynamic type?
    // If so, does the refresh interval correspond to acceptable limits.
    // Is there a possibility of overlap in advertised segments by any chance?
    // What does the spec mention regarding segment download continuity?
    return true;
}

bool timestampValidityCheck() {
    // Check the system timestamp
    // Check the published stream/MPD timestamp.
    // Compute offsets in system vs stream and any tz changes.
    // Do the observed timestamps tally with the stream milestones
    return true;
}

bool drmPresenceCheck() {
    // DRM associated with the stream?
    // DRM type?
    // License validity
    return true;
}

bool keyServerAvailabilityCheck() {
    // Is there a secure server defined for key fetch?
    // Presence of key server and downloadable property of the key.
    return true;
}

bool codecSupportCheck() {
    // Is the packaged codec decodable by the client?
    // Are the provided codec params supported by the decoder.
    return true;
}

bool versionsCheck() {
    // The version of the library currently supported by the client
    // Does the conformance framework work with the mentioned version.
    return true;
}

void ConformanceMPDCheckSequence::CheckCallback(std::string funcstr, std::int16_t status) {
    try {
        // Availability implies: presence on the server + download capability.
        // TODO: Apply mutex with a try_lock
        // checkmtx_.try_lock();

        if (bool(status) != this->checkStatus()) {
            changeCheckStatus(bool(status));
        }
    }
    catch (std::exception &e) {
        std::cerr << "'%s' URL: '%s'\n", funcstr, this->MPDURL();
        std::cerr << "'%s' Error: '%s'\n", funcstr, e.what();
        throw (funcstr + this->MPDURL() + "\n" + e.what());
    }
}

ConformanceMPDCheckSequence::ConformanceMPDCheckSequence(const std::string mpdurl) noexcept : mpdurl_(mpdurl) {

    // Find the schema type:
    std::string murl = this->MPDURL();

    // Find the URLscheme through prefix match.
    MPDURLSCHEMETYPE urlscheme = murl.substr(0, murl.find(HTTPPREFIX)).length() > 0 ? MPDURLSCHEMETYPE::HTTP_PREFIX :
                                 (murl.substr(0, murl.find(HTTPSPREFIX)).length() > 0 ? MPDURLSCHEMETYPE::HTTPS_PREFIX :
                                  MPDURLSCHEMETYPE::INVALID_PREFIX);
    // Set the scheme type.
    this->setMPDURLSchemeType(urlscheme);
    std::map<int16_t, std::function<void (std::string, std::int16_t)>> cfmap = this->checkFunctions();

    // Create a function table for each of the enumerated checks.
    for (int16_t enumIter = MPDCheckSequence::URLValidityCheck; enumIter != MPDCheckSequence::VersionsCheck+1; enumIter++) {

        switch (enumIter) {
            case MPDCheckSequence::URLValidityCheck: {
                 // constexpr auto funcpair = std::make_pair(&ConformanceMPDCheckSequence::checkURLValidity, &ConformanceMPDCheckSequence::CheckCallback);
                // Add the URLValidity check function and callback pair to the function table.
                // this->checkFunctions()->insert_or_assign(enumIter, funcpair);
                cfmap.insert_or_assign(enumIter, &ConformanceMPDCheckSequence::CheckCallback);
                break;
            }

            case MPDCheckSequence::AvailabilityCheck: {
                constexpr auto funcpair = std::make_pair(&ConformanceMPDCheckSequence::checkMPDAvailability,
                                               &ConformanceMPDCheckSequence::CheckCallback);
                cfmap.insert_or_assign(enumIter, &ConformanceMPDCheckSequence::CheckCallback);
                break;
            }

            case MPDCheckSequence::RedirectResponseCheck: {
                constexpr auto funcpair = std::make_pair(&ConformanceMPDCheckSequence::redirectResponseCheck,
                                               &ConformanceMPDCheckSequence::CheckCallback);
                cfmap.insert_or_assign(enumIter, &ConformanceMPDCheckSequence::CheckCallback);
                break;
            }

            case MPDCheckSequence::ManifestTypeCheck: {
                constexpr auto funcpair = std::make_pair(&ConformanceMPDCheckSequence::manifestTypeCheck,
                                               &ConformanceMPDCheckSequence::CheckCallback);
                cfmap.insert_or_assign(enumIter, &ConformanceMPDCheckSequence::CheckCallback);
                break;
            }

            case MPDCheckSequence::RefreshIntervalCheck: {
                constexpr auto funcpair = std::make_pair(&ConformanceMPDCheckSequence::refreshIntervalCheck,
                                               &ConformanceMPDCheckSequence::CheckCallback);
                cfmap.insert_or_assign(enumIter, &ConformanceMPDCheckSequence::CheckCallback);
                break;
            }

            case MPDCheckSequence::TimestampValidityCheck: {
                constexpr auto funcpair = std::make_pair(&ConformanceMPDCheckSequence::timestampValidityCheck,
                                               &ConformanceMPDCheckSequence::CheckCallback);
                cfmap.insert_or_assign(enumIter, &ConformanceMPDCheckSequence::CheckCallback);
                break;
            }

            case MPDCheckSequence::DRMPresenceCheck: {
                constexpr auto funcpair = std::make_pair(&ConformanceMPDCheckSequence::drmPresenceCheck,
                                               &ConformanceMPDCheckSequence::CheckCallback);
                cfmap.insert_or_assign(enumIter, &ConformanceMPDCheckSequence::CheckCallback);
                break;
            }

            case MPDCheckSequence::SecureStreamCheck: {
                constexpr auto funcpair = std::make_pair(&ConformanceMPDCheckSequence::secureStreamCheck,
                                               &ConformanceMPDCheckSequence::CheckCallback);
                cfmap.insert_or_assign(enumIter, &ConformanceMPDCheckSequence::CheckCallback);
                break;
            }

            case MPDCheckSequence::KeyServerAvailabilityCheck: {
                constexpr auto funcpair = std::make_pair(&ConformanceMPDCheckSequence::keyServerAvailabilityCheck,
                                               &ConformanceMPDCheckSequence::CheckCallback);
                cfmap.insert_or_assign(enumIter, &ConformanceMPDCheckSequence::CheckCallback);
                break;
            }

            case MPDCheckSequence::CodecSupportCheck: {
                constexpr auto funcpair = std::make_pair(&ConformanceMPDCheckSequence::codecSupportCheck,
                                               &ConformanceMPDCheckSequence::CheckCallback);
                cfmap.insert_or_assign(enumIter, &ConformanceMPDCheckSequence::CheckCallback);
                break;
            }

            case MPDCheckSequence::VersionsCheck: {
                constexpr auto funcpair = std::make_pair(&ConformanceMPDCheckSequence::versionsCheck,
                                               &ConformanceMPDCheckSequence::CheckCallback);
                cfmap.insert_or_assign(enumIter, &ConformanceMPDCheckSequence::CheckCallback);
                break;
            }

            default:
                break;
        }
    }
}

// TODO: Initiate the conformance check by thread-ID.
//const __thread_id initiateConformanceCheck() {
//
//    std::thread *mpdcheckThread = new std::thread();
//    std::thread::id mpdcheckID = mpdcheckThread->get_id();
//    std::thread::id mpdcheckID2 = mpdcheckThread->get_id();
//}

