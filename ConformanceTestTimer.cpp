//
// Created by Kamaldeep Tumkur on 28/08/20.
//

#include "ConformanceTestTimer.h"

using namespace std;
using namespace conformance::constraints;

std::size_t ConformanceTimerVariables::timeForConstraintCheckType(ConstraintTypes constraintType) {

    if (constraintType > conformance::constraints::ConstraintTypes::AkamaiCDNTokenConstraints ||
    constraintType < conformance::constraints::ConstraintTypes::ContentGenerationConstraints) {
        // Construct and raise the Conformance exception.
    };

    std::size_t checkTime = INVALID_CHECK_TIME;

    for (auto const&[constrainttype, chtime] : *constraintTimesMap_) {
        if (constrainttype == constraintType) {
            checkTime = chtime;
        }
    }

    return checkTime;
}

void ConformanceTimerVariables::setTimeForConstraintCheckType(ConstraintTypes ctype, std::size_t checktime) {
    try {
         std::size_t currentchecktime = constraintTimesMap_->at(ctype);
         std::size_t currenttotaltime = total_constraint_check_duration_;
         total_constraint_check_duration_ = currenttotaltime - currentchecktime + checktime;
         conformance_session_duration_ = conformance_session_duration_ - currenttotaltime + total_constraint_check_duration_;
    }
    catch (std::out_of_range) {
        // New entry. Add to the total time.
        total_constraint_check_duration_ += checktime;
        conformance_session_duration_ += checktime;
    }
    // Change to a ConformanceException type?
    catch (std::exception &e) {
        std::cerr << e.what() << std::endl;
    }

    constraintTimesMap_->insert_or_assign(ctype, checktime);
}



