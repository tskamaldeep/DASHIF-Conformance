//
// Created by Kamaldeep Tumkur on 28/08/20.
//

#ifndef DASHIF_CONFORMANCE_CONFORMANCETESTTIMER_H
#define DASHIF_CONFORMANCE_CONFORMANCETESTTIMER_H

#include <cmath>
#include <chrono>
#include <ctime>
#include <thread>
#include <map>
#include "ConformanceConstraints.h"

namespace conformance::constraints {

#define INVALID_CHECK_TIME -1

    using namespace std;
    class ConformanceTimerVariables {
    private:
        std::size_t mpd_download_duration_; // Just the cumulative time. No timing/performance stats for downloads.
        std::size_t mpd_parse_duration_; // Parse the manifest and populate the object structure.
        std::size_t total_constraint_check_duration_;
        std::size_t conformance_session_duration_;
        std::map<ConstraintTypes, std::size_t> *constraintTimesMap_ = new std::map<ConstraintTypes, std::size_t>();

    public:
        ConformanceTimerVariables(std::size_t downloadtime, std::size_t parsetime) :
        mpd_download_duration_(downloadtime), mpd_parse_duration_(parsetime), total_constraint_check_duration_(0){
           conformance_session_duration_ = downloadtime + parsetime + total_constraint_check_duration_;
        };

        std::size_t timeForConstraintCheckType(ConstraintTypes);

        void setTimeForConstraintCheckType(ConstraintTypes, std::size_t);
    };

    class ConformanceTestTimer {
    private:
        std::chrono::system_clock::time_point test_start_time_;
        std::chrono::system_clock::time_point test_stop_time_;

        ConformanceTimerVariables &timerVariables;

        // Threads and intervals.
        std::thread *timerthread = new std::thread();
        std::thread::id timerID = timerthread->get_id();
        // Sync with the conformance check thread.

    public:
        // Placeholder constructors.
        ConformanceTestTimer();
        ~ConformanceTestTimer();

    };
}

#endif //DASHIF_CONFORMANCE_CONFORMANCETESTTIMER_H
