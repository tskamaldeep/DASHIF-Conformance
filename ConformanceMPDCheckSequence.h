//
// Created by Kamaldeep Tumkur on 31/08/20.
//

#ifndef DASHIF_CONFORMANCE_CONFORMANCEMPDCHECKSEQUENCE_H
#define DASHIF_CONFORMANCE_CONFORMANCEMPDCHECKSEQUENCE_H

#include <cstdint>
#include <ctime>
#include <chrono>
#include <functional>
#include <optional>
// TODO: Add in threading per conformance check.
#include <thread>

#include <array>
#include "ConformanceConstraints.h"
#include "ConformanceException.h"

namespace conformance::download {
    using namespace std;

    enum MPDCheckSequence : std::int16_t const {
    URLValidityCheck = 0,
            AvailabilityCheck,
            RedirectResponseCheck,
            ManifestTypeCheck,
            RefreshIntervalCheck,
            TimestampValidityCheck,
            DRMPresenceCheck,
            SecureStreamCheck,
            KeyServerAvailabilityCheck,
            CodecSupportCheck,
            VersionsCheck,
};

enum MPDURLSCHEMETYPE : std::int16_t const {
    HTTP_PREFIX = 0,
    HTTPS_PREFIX,
    INVALID_PREFIX
};

enum MPDCHECK_THREADSTATUS : std::int16_t {
    INIT_STATUS = 0,
    STARTED_STATUS = 1,
    PROGRESS_STATUS = 2,
    SUSPENDED_STATUS = 3,
    STOPPED_STATUS = 4,
    CLEANUP_STATUS = 5,
};

// Define a map of a function and corresponding callback.
#if !defined(CHECKTIMESTAMPTYPE)
#define CHECKTIMESTAMPTYPE std::chrono::system_clock::time_point
#endif

__thread_id initiateWorkerThread() {
    std::thread *checkThread = new std::thread();
    return checkThread->get_id();
}

const std::string MPDEXT = ".mpd";
const std::string PATHSEP = "/";
const std::string HTTPPREFIX = "http://";
const std::string HTTPSPREFIX = "https://";

class ConformanceMPDCheckSequence {
private:
    // Invoking multiple URL checks?
    std::string mpdurl_;
    // Initialize to HTTPS type by default.
    MPDURLSCHEMETYPE schemetype_ = MPDURLSCHEMETYPE::HTTPS_PREFIX;
    int16_t checkStatus_ = MPDCHECK_THREADSTATUS::INIT_STATUS;

    // Initialize the times.
    CHECKTIMESTAMPTYPE initStatusTime = currentSystemTime();

    // Set to the uninitialized time instance. Then set when the mentioned phase begins.
    CHECKTIMESTAMPTYPE *startedStatusTime = NULL;
    CHECKTIMESTAMPTYPE *progressStatusTime = NULL;
    CHECKTIMESTAMPTYPE *suspendedStatusTime = NULL;
    CHECKTIMESTAMPTYPE *stoppedStatusTime = NULL;
    CHECKTIMESTAMPTYPE *cleanupStatusTime = NULL;

    // Applicable constraints for MPD Check.
    // TODO: Make the array to be per constraint type.
    std::array<std::int16_t, 2> *MPDTypeCheckConstraints = new std::array<std::int16_t, 2>{
            conformance::constraints::StaticMPDConstraints, \
            conformance::constraints::DynamicMPDConstraints, \
};

    std::array<std::int16_t, 2> *MPDResponseConstraints_ = new std::array<std::int16_t, 2>{
            conformance::constraints::HTTPSDownloadConstraints, \
            conformance::constraints::CaptioningMediaConstraints, \
};

    std::array<std::int16_t, 2> *drmPresenceCheckConstraints = new std::array<std::int16_t, 2>{
            conformance::constraints::EncryptedMediaConstraints, \
            conformance::constraints::KeyServerConstraints
    };

    std::array<std::int16_t, 2> *codecConstraints = new std::array<std::int16_t, 2>{
            conformance::constraints::ContentGenerationConstraints, \
            conformance::constraints::CMediaSegmentConstraints,
    };

    std::array<std::int16_t, 3> *clockConstraints = new std::array<std::int16_t, 3>{
            conformance::constraints::ClockConstraints, \
            conformance::constraints::MPDUpdateConstraints, \
            conformance::constraints::MPDTimelineConstraints
    };

    std::array<std::int16_t, 1> *versionConstraints = new std::array<std::int16_t, 1>{
            conformance::constraints::VersionsConstraints
    };

    // TODO: Define clock for timing checks. Alternatively, implement the test timer class.
    // Clock variables.
    // std::chrono::system_clock::time_point sysclock;
    // ConformanceTestTimer *testTimer = ....

public:
    ConformanceMPDCheckSequence() {};

    ConformanceMPDCheckSequence(const std::string mpdurl);

    const std::string MPDURL() { return mpdurl_; }

    const MPDURLSCHEMETYPE MPDURLSchemeType() { return schemetype_; }

    void setMPDURLSchemeType(MPDURLSCHEMETYPE stype) { schemetype_ = stype; }

    int16_t checkStatus() { return checkStatus_; }

    CHECKTIMESTAMPTYPE currentSystemTime() { return std::chrono::system_clock::now(); }

    void changeCheckStatus(int16_t status) { checkStatus_ = status; }

    // const __thread_id initiateConformanceCheck() const;
    // const bool currentConformanceCheckStatus(const __thread_id tid) noexcept;

    // TODO: Implement the destructor.
    ~ConformanceMPDCheckSequence() = default;

    // All the check functions.
    bool checkURLValidity();

    bool checkMPDAvailability();

    bool redirectResponseCheck();

    bool manifestTypeCheck();

    bool refreshIntervalCheck();

    bool timestampValidityCheck();

    bool drmPresenceCheck();

    bool secureStreamCheck();

    bool keyServerAvailabilityCheck();

    bool codecSupportCheck();

    bool versionsCheck();

    // Callback function.
    void CheckCallback(std::string, std::int16_t);
};

}

#endif //DASHIF_CONFORMANCE_CONFORMANCEMPDCHECKSEQUENCE_H
