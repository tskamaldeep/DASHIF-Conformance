//
// Created by Kamaldeep Tumkur on 26/08/20.
//

#ifndef DASHIF_CONFORMANCE_CONFORMANCEERRORLEVELS_H
#define DASHIF_CONFORMANCE_CONFORMANCEERRORLEVELS_H

#include <cstdint>
#include <iterator>
#include <typeinfo>
#include "ConformanceException.h"

namespace conformance::exception {

#if !defined(ERRORHASH) && !defined(ERRORSTRING)
#define ERRORHASH std::hash<std::string>{}
#define ERRORSTRINGPAIR std::pair<const std::size_t, const std::size_t>
#define ERRORCOLORCODEPAIR std::pair<const std::size_t, ErrorColorCode>
#endif

    using namespace std;

    enum ErrorColorCode : std::int16_t {
        RED = 0,
        AMBER,
        YELLOW,
        GRAY,
        WHITE,
        GREEN
    };

    enum ConformanceErrorTypes : std::int16_t {
        FATAL = 0,
        ERROR,
        WARNING,
        DEBUG,
        INFO,
        VERBOSE
    };

    enum ConformanceEnforcementTypes : std::int16_t {
        OPTIONAL = 0,
        MAY,
        MAY_NOT,
        RECOMMENDED,
        SHALL,
        SHALL_NOT,
        SHOULD,
        SHOULD_NOT,
        REQUIRED,
        MUST,
        MUST_NOT,
    };


    const std::string DASHIF_CONFORMANCE_FATAL = "FATAL";

    const std::string DASHIF_CONFORMANCE_ERROR = "ERROR";

    const std::string DASHIF_CONFORMANCE_WARNING = "WARNING";

    const std::string DASHIF_CONFORMANCE_DEBUG = "DEBUG";

    const std::string DASHIF_CONFORMANCE_INFO = "INFO";

    const std::string DASHIF_CONFORMANCE_VERBOSE = "VERBOSE";

// Conformance Enforcements
// HASHES REQD.?
    const std::string DASHIF_CONFORMANCE_MUST = "MUST";

    const std::string DASHIF_CONFORMANCE_SHOULD = "SHOULD";

    const std::string DASHIF_CONFORMANCE_REQUIRED = "REQUIRED";

    const std::string DASHIF_CONFORMANCE_RECOMMENDED = "RECOMMENDED";

    const std::string DASHIF_CONFORMANCE_MAY = "MAY";

    const std::string DASHIF_CONFORMANCE_OPTIONAL = "OPTIONAL";

    const std::string DASHIF_CONFORMANCE_SHOULD_NOT = "SHOULD_NOT";

    const std::string DASHIF_CONFORMANCE_SHALL_NOT = "SHALL_NOT";

    const std::string DASHIF_CONFORMANCE_MUST_NOT = "MUST_NOT";

    // Set the default error level only for display purposes.
    ConformanceErrorTypes DEFAULT_DASHIF_CONFORMANCE_ERROR_LEVEL = ConformanceErrorTypes::DEBUG;
    ErrorColorCode DEFAULT_DASHIF_CONFORMANCE_ERROR_COLOR_CODE = ErrorColorCode::GRAY;

    // Set the minimum error enforcement level, for conformance check purposes.
    ConformanceEnforcementTypes DEFAULT_DASHIF_CONFORMANCE_MIN_ENFORCEMENT_LEVEL = ConformanceEnforcementTypes::RECOMMENDED;

    class ConformanceErrorLevels {
    private:
        std::list<ConformanceException *> *conformanceExceptions = new std::list<ConformanceException *>();

        std::map<ConformanceErrorTypes, const std::size_t> *conformanceErrorMap_ =
                new std::map<ConformanceErrorTypes, const std::size_t>();

        std::map<ErrorColorCode, const std::size_t> *colorcodeErrorMap_ =
                new std::map<ErrorColorCode, const std::size_t>();

        std::map<ConformanceEnforcementTypes, const std::size_t> *enforcementErrorMap_ =
                new std::map<ConformanceEnforcementTypes, const std::size_t>();

    public:

        void initializeConformanceMaps();

        ConformanceErrorLevels();

        ConformanceErrorLevels( ConformanceEnforcementTypes);

        ~ConformanceErrorLevels();

        void setDefaultConformanceErrorLevel(ConformanceErrorTypes errorLevel);

        void setDefaultEnforcementErrorLevel(ConformanceEnforcementTypes);

        std::map<ErrorColorCode, const std::size_t> *colorcodeErrorMap() { return colorcodeErrorMap_; }

        std::map<ConformanceErrorTypes, const std::size_t> *conformanceErrorMap() { return conformanceErrorMap_; }

        std::map<ConformanceEnforcementTypes, const std::size_t> *enforcementsErrorMap() { return enforcementErrorMap_; }

        ConformanceErrorTypes errorLevelForConformanceEnforcementType(ConformanceEnforcementTypes errtype);

        ErrorColorCode errorColorCodeForConformanceErrorType(ConformanceErrorTypes errlevel);
    };

}


#endif //DASHIF_CONFORMANCE_CONFORMANCEERRORLEVELS_H
