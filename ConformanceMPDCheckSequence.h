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
#include <cfloat>

#include "ConformanceConstraints.h"
#include "ConformanceException.h"

namespace conformance::download {
    using namespace std;

    enum MPDCheckSequence : std::int16_t {
        URLValidityCheck = 0,
        ManifestTypeCheck,
        AdaptationSetCheck,
        DRMPresenceCheck,
        SecureStreamCheck,
        KeyServerAvailabilityCheck,
        CodecSupportCheck,
        VersionsCheck,
        MPDAvailabilityCheck,
        RedirectResponseCheck,
        RefreshIntervalCheck,
        TimestampValidityCheck
    };

    enum MPDURLSCHEMETYPE : std::int16_t {
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
        CLEANUP_STATUS = 5
    };

// Define a map of a function and corresponding callback.
#if !defined(CHECKTIMESTAMPTYPE) || !defined(CHECKFUNCTIONSMAP)
#define CHECKFUNCTIONSMAP std::map<std::int16_t, std::function<bool()>>
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

    // Namespace requirement here.
    using namespace conformance::constraints;

    class ConformanceMPDCheckSequence {
    private:
        // Invoking multiple URL checks?
        std::string mpdurl_;
        // Initialize to HTTPS type by default.
        MPDURLSCHEMETYPE schemetype_ = MPDURLSCHEMETYPE::HTTPS_PREFIX;
        int16_t checkStatus_ = MPDCHECK_THREADSTATUS::INIT_STATUS;

        // Initialize the times.
        CHECKTIMESTAMPTYPE initStatusTime_;
        double processTime_ = 0;

        // Set to the uninitialized time instance. Then set when the mentioned phase begins.
        CHECKTIMESTAMPTYPE *startedStatusTime_ = NULL;
        CHECKTIMESTAMPTYPE *progressStatusTime_ = NULL;
        CHECKTIMESTAMPTYPE *suspendedStatusTime_ = NULL;
        CHECKTIMESTAMPTYPE *stoppedStatusTime_ = NULL;
        CHECKTIMESTAMPTYPE *cleanupStatusTime_ = NULL;

        // Applicable constraints for MPD Check.
        // TODO: Make the array to be per constraint type.
        std::array<std::size_t, 2> *MPDTypeCheckConstraints = new std::array<std::size_t, 2> {
                ConstraintTypes::DynamicMPDConstraints,
                ConstraintTypes::StaticMPDConstraints

        };

        std::array<std::size_t, 4> *AdaptationSetConstraints = new std::array<std::size_t, 4> {
                ConstraintTypes::VideoAdaptationSetConstraints,
                ConstraintTypes::AudioAdaptationSetConstraints,
                ConstraintTypes::TextAdaptationSetConstraints,
                ConstraintTypes::SegmentTemplateConstraints
        };

        std::array<std::size_t, 4> *MPDResponseConstraints_ = new std::array<std::size_t, 4> {
                ConstraintTypes::HTTPSDownloadConstraints,
                ConstraintTypes::CaptioningMediaConstraints,
                ConstraintTypes::EndOfLiveConstraints,
                ConstraintTypes::MPDUpdateConstraints
        };

        std::array<std::size_t, 2> *drmPresenceCheckConstraints = new std::array<std::size_t, 2> {
                ConstraintTypes::EncryptedMediaConstraints,
                ConstraintTypes::KeyServerConstraints
        };

        std::array<std::size_t, 2> *codecConstraints = new std::array<std::size_t, 2> {
                ConstraintTypes::ContentGenerationConstraints,
                ConstraintTypes::CMediaSegmentConstraints
        };

        std::array<std::size_t, 2> *clockConstraints = new std::array<std::size_t, 2> {
                ConstraintTypes::ClockConstraints,
                ConstraintTypes::MPDTimelineConstraints
        };

        std::array<std::size_t, 1> *versionConstraints = new std::array<std::size_t, 1> {
                ConstraintTypes::VersionsConstraints
        };

        std::array<std::size_t, 1> *dvbConstraints = new std::array<std::size_t, 1> {
                ConstraintTypes::DVBDASHConstraints
        };

        std::array<std::size_t, 1> *tokenConstraints = new std::array<std::size_t, 1> {
                ConstraintTypes::AkamaiCDNTokenConstraints
        };

        // TODO: Define clock for timing checks. Alternatively, implement the test timer class.
        // Clock variables.
        // std::chrono::system_clock::time_point sysclock;
        // ConformanceTestTimer *testTimer = ....
        CHECKFUNCTIONSMAP *checkFunctions_ = new std::map<std::int16_t, std::function<bool()>>();

    public:
        ConformanceMPDCheckSequence(const std::string mpdurl);

        const std::string MPDURL() { return mpdurl_; }

        const MPDURLSCHEMETYPE MPDURLSchemeType() { return schemetype_; }

        void setMPDURLSchemeType(MPDURLSCHEMETYPE stype) { schemetype_ = stype; }

        int16_t checkStatus() { return checkStatus_; }

        CHECKFUNCTIONSMAP *checkFunctions() { return checkFunctions_; }

        CHECKTIMESTAMPTYPE currentSystemTime() { return std::chrono::system_clock::now(); }

        CHECKTIMESTAMPTYPE initSystemTimeStamp() { return initStatusTime_; }

        double processSystemTime() { return processTime_; }

        CHECKTIMESTAMPTYPE *startedSystemTimeStamp() { return startedStatusTime_; }

        CHECKTIMESTAMPTYPE *progressSystemTimeStamp() { return progressStatusTime_; }

        CHECKTIMESTAMPTYPE *suspendedSystemTimeStamp() { return suspendedStatusTime_; }

        CHECKTIMESTAMPTYPE *stoppedSystemTimeStamp() { return stoppedStatusTime_; }

        CHECKTIMESTAMPTYPE *cleanupSystemTimeStamp() { return cleanupStatusTime_; }

        double timeDiffInMilliSeconds(CHECKTIMESTAMPTYPE latertime, CHECKTIMESTAMPTYPE earliertime);

        double timeDiffInSeconds(CHECKTIMESTAMPTYPE latertime, CHECKTIMESTAMPTYPE earliertime);

        double timeDiffInMinutes(CHECKTIMESTAMPTYPE latertime, CHECKTIMESTAMPTYPE earliertime);

        void changeCheckStatus(int16_t status);

        // const __thread_id initiateConformanceCheck() const;
        // const bool currentConformanceCheckStatus(const __thread_id tid) noexcept;

        // TODO: Implement the destructor.
        ~ConformanceMPDCheckSequence() = default;

        // All the check functions.
        bool checkURLValidity();

        bool checkMPDAvailability();

        bool redirectResponseCheck();

        bool manifestTypeCheck();

        bool adaptationsetCheck();

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
