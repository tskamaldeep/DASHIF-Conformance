//
// Created by Kamaldeep Tumkur on 31/08/20.
//

#include <iostream>
#include <utility>
#include <memory>
#include "ConformanceMPDCheckSequence.h"

using namespace conformance::download;
using namespace conformance::exception;
using namespace std;

bool ConformanceMPDCheckSequence::checkURLValidity() {
    // Check the extension.
    // Check the prefix
    bool result = false;
    try {
        switch (this->MPDURLSchemeType()) {
            case conformance::download::MPDURLSCHEMETYPE::HTTP_PREFIX:
                // No HTTPS validations required if any.
                break;
            case conformance::download::MPDURLSCHEMETYPE::HTTPS_PREFIX:
                break;
            case conformance::download::MPDURLSCHEMETYPE::INVALID_PREFIX:
            default:
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

        const std::string PATHSEP = "/";
        // Find the path components.
        std::string murl = this->MPDURL();
        std::size_t firstsepindex = murl.find_first_of(PATHSEP);
        std::size_t lastsepindex = murl.find_last_of(PATHSEP);
        std::string urlbasename = murl.substr(lastsepindex + 1);
        std::string urldirname = murl.substr(firstsepindex + 1, lastsepindex);

        // TODO: Complete the URL construct check.
        result = true;
        return result;
    }
    catch (std::exception &e) {
        this->CheckCallback(e.what(), result);
        return result;
    }
}

bool ConformanceMPDCheckSequence::checkMPDAvailability() {
    // Check presence of the MPD
    // Check download validity.

    return true;
}

bool ConformanceMPDCheckSequence::redirectResponseCheck() {
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

    bool status = true;

    std::array<size_t, 2>::iterator *mpdtypecheckIter = new std::array<size_t, 2>::iterator();
    for (*mpdtypecheckIter = MPDResponseConstraints_->begin();
         *mpdtypecheckIter != MPDResponseConstraints_->end(); mpdtypecheckIter++) {
        constraints::ConformanceConstraint *typeConstraint = reinterpret_cast<constraints::ConformanceConstraint *>(*mpdtypecheckIter);
        // Get the set of definitions associated with the provided constraint of MPD type checks.

    }
    return status;
}

bool ConformanceMPDCheckSequence::refreshIntervalCheck() {
    // Is the manifest dynamic type?
    // If so, does the refresh interval correspond to acceptable limits.
    // Is there a possibility of overlap in advertised segments by any chance?
    // What does the spec mention regarding segment download continuity?
    return true;
}

bool ConformanceMPDCheckSequence::timestampValidityCheck() {
    // Check the system timestamp
    // Check the published stream/MPD timestamp.
    // Compute offsets in system vs stream and any tz changes.
    // Do the observed timestamps tally with the stream milestones
    return true;
}

bool ConformanceMPDCheckSequence::drmPresenceCheck() {
    // DRM associated with the stream?
    // DRM type?
    // License validity
    return true;
}

bool ConformanceMPDCheckSequence::keyServerAvailabilityCheck() {
    // Is there a secure server defined for key fetch?
    // Presence of key server and downloadable property of the key.
    return true;
}

bool ConformanceMPDCheckSequence::codecSupportCheck() {
    // Is the packaged codec decodable by the client?
    // Are the provided codec params supported by the decoder.
    return true;
}

bool ConformanceMPDCheckSequence::versionsCheck() {
    // The version of the library currently supported by the client
    // Does the conformance framework work with the mentioned version.
    return true;
}

double ConformanceMPDCheckSequence::timeDiffInMilliSeconds(std::chrono::system_clock::time_point latertime,
                                                           std::chrono::system_clock::time_point earliertime) {

    std::size_t epochMilliSecsLaterTime = std::chrono::duration_cast<std::chrono::milliseconds>(
            latertime.time_since_epoch()).count();

    std::size_t epochMilliSecsEarlierTime = std::chrono::duration_cast<std::chrono::milliseconds>(
            earliertime.time_since_epoch()).count();

    return (epochMilliSecsLaterTime - epochMilliSecsEarlierTime);
}

double ConformanceMPDCheckSequence::timeDiffInSeconds(std::chrono::system_clock::time_point latertime,
                                                      std::chrono::system_clock::time_point earliertime) {

    double milliSecs = this->timeDiffInMilliSeconds(latertime, earliertime);
    return (((float) milliSecs) / 1000);
}

double ConformanceMPDCheckSequence::timeDiffInMinutes(std::chrono::system_clock::time_point latertime,
                                                      std::chrono::system_clock::time_point earliertime) {

    double secs = this->timeDiffInSeconds(latertime, earliertime);
    return (((float) secs) / 60);
}

void ConformanceMPDCheckSequence::changeCheckStatus(int16_t status) {
    if (status > MPDCHECK_THREADSTATUS::CLEANUP_STATUS ||
        status < MPDCHECK_THREADSTATUS::INIT_STATUS) {
        // Prepare and send a ConformanceException?
        std::cerr << "Invalid status provided for updation" << std::endl;
        return;
    }

    int16_t curstatus = this->checkStatus();
    if (curstatus == MPDCHECK_THREADSTATUS::SUSPENDED_STATUS &&
        status < curstatus &&
        status != MPDCHECK_THREADSTATUS::PROGRESS_STATUS) {
        std::cerr << "Invalid status updation:\n " << "Current Status: " << endl;
        return;
    }
    ///////////////////////////////
    // TODO:
    ///////////////////////////////

    try {
        checkStatus_ = std::move(status);

        switch (status) {
            case (INIT_STATUS):
                initStatusTime_ = this->currentSystemTime();
                break;
            case (STARTED_STATUS):
                *startedStatusTime_ = this->currentSystemTime();
                break;
            case (PROGRESS_STATUS):
                *progressStatusTime_ = this->currentSystemTime();
                break;
            case (SUSPENDED_STATUS):
                *suspendedStatusTime_ = this->currentSystemTime();
                break;
            case (STOPPED_STATUS):
                *stoppedStatusTime_ = this->currentSystemTime();
                break;
            case (CLEANUP_STATUS):
                *cleanupStatusTime_ = this->currentSystemTime();
                break;
            default:
                break;
        }
    }
    catch (std::exception &e) {
        std::cerr << "Change status of MPD Check Sequence Exception:\n " << e.what() << std::endl;
    }
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

ConformanceMPDCheckSequence::ConformanceMPDCheckSequence(const std::string mpdurl) : mpdurl_(mpdurl) {

    // Find the schema type:
    std::string murl = this->MPDURL();

    // Find the URLscheme through prefix match.
    MPDURLSCHEMETYPE urlscheme = murl.substr(0, murl.find(HTTPPREFIX)).length() > 0 ? MPDURLSCHEMETYPE::HTTP_PREFIX :
                                 (murl.substr(0, murl.find(HTTPSPREFIX)).length() > 0 ? MPDURLSCHEMETYPE::HTTPS_PREFIX :
                                  MPDURLSCHEMETYPE::INVALID_PREFIX);
    // Set the scheme type.
    this->setMPDURLSchemeType(urlscheme);
    // std::map<int16_t, std::function<void (std::string, std::int16_t)>> cfmap = this->checkFunctions();

    // Carry the check functions map.
    CHECKFUNCTIONSMAP *checkfuncs = this->checkFunctions();

    // Create a function table for each of the enumerated checks.

    for (int16_t enumIter = MPDCheckSequence::URLValidityCheck;
         enumIter != MPDCheckSequence::VersionsCheck + 1; enumIter++) {
        switch (enumIter) {
            case MPDCheckSequence::URLValidityCheck: {
//                checkfuncs->try_emplace(enumIter, &ConformanceMPDCheckSequence::checkURLValidity);
                // checkfuncs->insert_or_assign(enumIter, &ConformanceMPDCheckSequence::checkURLValidity);
                // checkfuncs->insert_or_assign(enumIter, std::make_pair(enumIter, &ConformanceMPDCheckSequence::checkURLValidity));
                break;
            }

            case MPDCheckSequence::AvailabilityCheck: {
//                checkfuncs->insert_or_assign(enumIter, &ConformanceMPDCheckSequence::checkMPDAvailability);
                break;
            }

            case MPDCheckSequence::RedirectResponseCheck: {
//                checkfuncs->insert_or_assign(enumIter, &ConformanceMPDCheckSequence::redirectResponseCheck);
                break;
            }

            case MPDCheckSequence::ManifestTypeCheck: {
                break;
            }

            case MPDCheckSequence::RefreshIntervalCheck: {
                break;
            }

            case MPDCheckSequence::TimestampValidityCheck: {
                break;
            }

            case MPDCheckSequence::DRMPresenceCheck: {
                break;
            }

            case MPDCheckSequence::SecureStreamCheck: {
                break;
            }

            case MPDCheckSequence::KeyServerAvailabilityCheck: {
                break;
            }

            case MPDCheckSequence::CodecSupportCheck: {
                break;
            }

            case MPDCheckSequence::VersionsCheck: {
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

